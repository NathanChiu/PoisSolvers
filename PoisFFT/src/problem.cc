// @file:     problem.cc
// @author:   Samuel
// @created:  2017.08.23
// @editted:  2017.08.23 - Samuel
// @license:  GNU LGPL v3
//
// @desc:     Definition of the problem - dbdot loc, material properties, etc.

#include "problem.h"

using namespace phys;

// Constructor
Problem::Problem(const std::string &fname)
{
  initProblem();
  readProblem(fname);
}


void Problem::initProblem()
{
  elec_tree = std::make_shared<Problem::Aggregate>();
}


// aggregate
int Problem::Aggregate::size()
{
  int n_elecs=elecs.size();
  if(!aggs.empty())
    for(auto agg : aggs)
      n_elecs += agg->size();
  return n_elecs;
}


// ELEC ITERATOR
Problem::ElecIterator::ElecIterator(std::shared_ptr<Aggregate> root, bool begin)
{
  if(begin){
    // keep finding deeper aggregates until one that contains dbs is found
    while(root->elecs.empty() && !root->aggs.empty()) {
      push(root);
      root = root->aggs.front();
    }
    push(root);
  }
  else{
    elec_iter = root->elecs.cend();
  }
}


Problem::ElecIterator& Problem::ElecIterator::operator++()
{
  // exhaust the current Aggregate DBs first
  if(elec_iter != curr->elecs.cend())
    return ++elec_iter != curr->elecs.cend() ? *this : ++(*this);

  // if available, push the next aggregate onto the stack
  if(agg_stack.top().second != curr->aggs.cend()){
    push(*agg_stack.top().second);
    return elec_iter != curr->elecs.cend() ? *this : ++(*this);
  }

  // aggregate is complete, pop off stack
  pop();
  return agg_stack.size() == 0 ? *this : ++(*this);
}


void Problem::ElecIterator::push(std::shared_ptr<Aggregate> agg)
{
  if(!agg_stack.empty())
    ++agg_stack.top().second;
  agg_stack.push(std::make_pair(agg, agg->aggs.cbegin()));
  elec_iter = agg->elecs.cbegin();
  curr = agg;
}


void Problem::ElecIterator::pop()
{
  agg_stack.pop();              // pop complete aggregate off stack
  if(agg_stack.size() > 0){
    curr = agg_stack.top().first; // update current to new top
    elec_iter = curr->elecs.cend();   // don't reread dbs
  }
}


// FILE HANDLING
// parse problem XML, return true if successful
bool Problem::readProblem(const std::string &fname)
{
  std::cout << "Reading problem file: " << fname << std::endl;

  bpt::ptree tree; // create empty property tree object
  bpt::read_xml(fname, tree, bpt::xml_parser::no_comments); // parse the input file into property tree
  // TODO catch read error exception

  // parse XML

  // read program properties
  // TODO read program node

  // read material properties
  // TODO read material_prop node

  // read simulation parameters
  std::cout << "Read simulation parameters" << std::endl;
  if(!readSimulationParam(tree.get_child("dbdesigner.sim_params")))
    return false;

  // read items
  std::cout << "Read items tree" << std::endl;
  if(!readDesign(tree.get_child("dbdesigner.design"), elec_tree))
    return false;

  //return true;
  return false;
}


bool Problem::readProgramProp(const bpt::ptree &program_prop_tree)
{
  for (bpt::ptree::value_type const &v : program_prop_tree) {
    program_props.insert(std::map<std::string, std::string>::value_type(v.first, v.second.data()));
    std::cout << "ProgramProp: Key=" << v.first << ", Value=" << program_props[v.first] << std::endl;
  }
  return true;
}


bool Problem::readMaterialProp(const bpt::ptree &material_prop_tree)
{
  (void)material_prop_tree; // function to be implemented, suppress variable unused warning for now
  return true;
}


bool Problem::readSimulationParam(const bpt::ptree &sim_params_tree)
{
  for (bpt::ptree::value_type const &v : sim_params_tree) {
    sim_params.insert(std::map<std::string, std::string>::value_type(v.first, v.second.data()));
    std::cout << "SimParam: Key=" << v.first << ", Value=" << sim_params[v.first] << std::endl;
  }
  return true;
}


bool Problem::readDesign(const bpt::ptree &subtree, const std::shared_ptr<Aggregate> &agg_parent)
{
  std::cout << "Beginning to read design" << std::endl;
  for (bpt::ptree::value_type const &layer_tree : subtree) {
    std::string layer_type = layer_tree.second.get<std::string>("<xmlattr>.type");
    if (!layer_type.compare("DB")) {
      std::cout << "Encountered node " << layer_tree.first << " with type " << layer_type << ", entering" << std::endl;
      readItemTree(layer_tree.second, agg_parent);
    } else if (!layer_type.compare("Electrode")) {
    // if (!layer_type.compare("Electrode")) {
      // std::cout << "TODO write code for parsing electrodes" << std::endl;
      std::cout << "Encountered node " << layer_tree.first << " with type " << layer_type << ", entering" << std::endl;
      readItemTree(layer_tree.second, agg_parent);
    } else {
      std::cout << "Encountered node " << layer_tree.first << " with type " << layer_type << ", no defined action for this layer. Skipping." << std::endl;
    }
  }
  return true;
}


bool Problem::readItemTree(const bpt::ptree &subtree, const std::shared_ptr<Aggregate> &agg_parent)
{
  for (bpt::ptree::value_type const &item_tree : subtree) {
    std::string item_name = item_tree.first;

    if (!item_name.compare("aggregate")) {
      // add aggregate child to tree
      agg_parent->aggs.push_back(std::make_shared<Aggregate>());
      readItemTree(item_tree.second, agg_parent->aggs.back());
    // } else if (!item_name.compare("dbdot")) {
    //   // add DBDot to tree
    //   readDBDot(item_tree.second, agg_parent);
    } else if (!item_name.compare("electrode")) {
      // add Electrode to tree
      readElectrode(item_tree.second, agg_parent);
    } else {
      std::cout << "Encountered unknown item node: " << item_tree.first << std::endl;
    }
  }
  return true;
}


bool Problem::readElectrode(const bpt::ptree &subtree, const std::shared_ptr<Aggregate> &agg_parent)
{
  float x1, x2, y1, y2;
  float potential;

  // read values from XML stream
  potential = subtree.get<float>("potential");
  x1 = subtree.get<float>("dim.<xmlattr>.x1");
  x2 = subtree.get<float>("dim.<xmlattr>.x2");
  y1 = subtree.get<float>("dim.<xmlattr>.y1");
  y2 = subtree.get<float>("dim.<xmlattr>.y2");

  agg_parent->elecs.push_back(std::make_shared<Electrode>(x1,x2,y1,y2,potential));

  std::cout << "Electrode created with x1=" << agg_parent->elecs.back()->x1 << ", y1=" << agg_parent->elecs.back()->y1 <<
    ", x2=" << agg_parent->elecs.back()->x2 << ", y2=" << agg_parent->elecs.back()->y2 <<
    ", potential=" << agg_parent->elecs.back()->potential << std::endl;

  return true;
}
