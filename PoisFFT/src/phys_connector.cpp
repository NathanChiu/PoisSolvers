// @file:     phys_engine.cc
// @author:   Samuel
// @created:  2017.08.23
// @editted:  2017.08.23 - Samuel
// @license:  GNU LGPL v3
//
// @desc:     Base class for physics engines

#include "phys_connector.h"
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace phys;


//CONSTRUCTOR
PhysicsConnector::PhysicsConnector(const std::string &eng_name_in,
  const std::string &input_path_in, const std::string &output_path_in)
{
  eng_name = eng_name_in;
  input_path = input_path_in;
  output_path = output_path_in;
  // initProblem();
  // readProblem(input_path);
}


//What used to be problem

void PhysicsConnector::initProblem(void)
{
  elec_tree = std::make_shared<PhysicsConnector::Aggregate>();
}

// aggregate
int PhysicsConnector::Aggregate::size()
{
  int n_elecs=elecs.size();
  if(!aggs.empty())
    for(auto agg : aggs)
      n_elecs += agg->size();
  return n_elecs;
}

// ELEC ITERATOR
PhysicsConnector::ElecIterator::ElecIterator(std::shared_ptr<Aggregate> root, bool begin)
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

PhysicsConnector::ElecIterator& PhysicsConnector::ElecIterator::operator++()
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

void PhysicsConnector::ElecIterator::push(std::shared_ptr<Aggregate> agg)
{
  if(!agg_stack.empty())
    ++agg_stack.top().second;
  agg_stack.push(std::make_pair(agg, agg->aggs.cbegin()));
  elec_iter = agg->elecs.cbegin();
  curr = agg;
}

void PhysicsConnector::ElecIterator::pop()
{
  agg_stack.pop();              // pop complete aggregate off stack
  if(agg_stack.size() > 0){
    curr = agg_stack.top().first; // update current to new top
    elec_iter = curr->elecs.cend();   // don't reread dbs
  }
}

// FILE HANDLING
// parse problem XML, return true if successful
bool PhysicsConnector::readProblem(const std::string &fname)
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

bool PhysicsConnector::readProgramProp(const bpt::ptree &program_prop_tree)
{
  for (bpt::ptree::value_type const &v : program_prop_tree) {
    program_props.insert(std::map<std::string, std::string>::value_type(v.first, v.second.data()));
    std::cout << "ProgramProp: Key=" << v.first << ", Value=" << program_props[v.first] << std::endl;
  }
  return true;
}

bool PhysicsConnector::readMaterialProp(const bpt::ptree &material_prop_tree)
{
  (void)material_prop_tree; // function to be implemented, suppress variable unused warning for now
  return true;
}

bool PhysicsConnector::readSimulationParam(const bpt::ptree &sim_params_tree)
{
  for (bpt::ptree::value_type const &v : sim_params_tree) {
    sim_params.insert(std::map<std::string, std::string>::value_type(v.first, v.second.data()));
    std::cout << "SimParam: Key=" << v.first << ", Value=" << sim_params[v.first] << std::endl;
  }
  return true;
}

bool PhysicsConnector::readDesign(const bpt::ptree &subtree, const std::shared_ptr<Aggregate> &agg_parent)
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

bool PhysicsConnector::readItemTree(const bpt::ptree &subtree, const std::shared_ptr<Aggregate> &agg_parent)
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

bool PhysicsConnector::readElectrode(const bpt::ptree &subtree, const std::shared_ptr<Aggregate> &agg_parent)
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




















//what used to be physeng
void PhysicsConnector::helloWorld(void)
{
  std::cout << "PhysicsConnector instantiated." << std::endl;
  std::cout << eng_name << ", " << input_path << ", " << output_path << std::endl;
}


void PhysicsConnector::writeResultsXml()
{
  std::cout << "PhysicsConnector::writeResultsXML()" << std::endl;
  // define major XML nodes
  boost::property_tree::ptree tree;
  boost::property_tree::ptree node_root;       // <sim_out>
  boost::property_tree::ptree node_eng_info;   // <eng_info>
  boost::property_tree::ptree node_sim_params; // <sim_params>
  boost::property_tree::ptree node_electrode;  // <electrode>
  boost::property_tree::ptree node_potential_map;  // <potential>

  std::cout << "Write results to XML..." << std::endl;
  // NOTE in the future, there's probably a range of stuff that can be exported.
  // for now, only export charge config

  // eng_info
  node_eng_info.put("engine", "PoisSolver");
  node_eng_info.put("version", "TBD"); // TODO real version

  // sim_params
  // TODO

  // electrode
  for (auto elec : elec_vec) {
    boost::property_tree::ptree node_dim;
    node_dim.put("<xmlattr>.x1", (std::to_string((elec.x[0]-SimParams::xoffset)/SimParams::finalscale/SimParams::Ls[0]).c_str()));
    node_dim.put("<xmlattr>.y1", (std::to_string((elec.y[0]-SimParams::yoffset)/SimParams::finalscale/SimParams::Ls[1]).c_str()));
    node_dim.put("<xmlattr>.x2", (std::to_string((elec.x[1]-SimParams::xoffset)/SimParams::finalscale/SimParams::Ls[0]).c_str()));
    node_dim.put("<xmlattr>.y2", (std::to_string((elec.y[1]-SimParams::yoffset)/SimParams::finalscale/SimParams::Ls[1]).c_str()));
    node_electrode.add_child("dim", node_dim);
    boost::property_tree::ptree node_pot;
    node_pot.put("", std::to_string(elec.potential).c_str());
    node_electrode.add_child("potential", node_pot);
  }

  //potential_map
  const int k = SimParams::ns[2]/2;
  for (int i = 0; i < SimParams::ns[0]; i++){
    for (int j = 0; j < SimParams::ns[1]; j++){
      //create each entry
      // std::cout << arr[SimParams::IND(i,j,k)] << ", " << std::to_string(arr[SimParams::IND(i,j,k)]).c_str() << std::endl;
      boost::property_tree::ptree node_potential_val;
      node_potential_val.put("<xmlattr>.x", (std::to_string((i*SimParams::ds[0]-SimParams::xoffset)/SimParams::finalscale/SimParams::Ls[0])).c_str());
      node_potential_val.put("<xmlattr>.y", (std::to_string((j*SimParams::ds[1]-SimParams::yoffset)/SimParams::finalscale/SimParams::Ls[1])).c_str());
      node_potential_val.put("<xmlattr>.val", (std::to_string(arr[SimParams::IND(i,j,k)]).c_str()));
      node_potential_map.add_child("potential_val", node_potential_val);
    }
  }
  node_root.add_child("eng_info", node_eng_info);
  node_root.add_child("electrode", node_electrode);
  node_root.add_child("potential_map", node_potential_map);
  tree.add_child("sim_out", node_root);

  // write to file
  boost::property_tree::write_xml(output_path, tree, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>(' ',4));

  std::cout << "Write to XML complete." << std::endl;
}