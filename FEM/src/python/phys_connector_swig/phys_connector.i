%module phys_connector
%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>
%include <exception.i>

%{
#include "phys_connector.h"
%}

namespace std {
    %template(IntVector) vector<int>;
    %template(StringPair) pair<string, string>;
    %template(StringPairVector) vector< pair<string, string> >;
    %template(StringVector) vector<string>;
    %template(StringVector2D) vector< vector<string> >;
}

%{
#define SWIG_FILE_WITH_INIT
#define SWIG_PYTHON_2_UNICODE
%}

%include "phys_connector.h"

%feature("shadow") phys::DBIterator::__next__() %{
  def __next__(self):
    db = $action(self)
    if db == None:
      raise StopIteration
    else:
      return db
%}

%extend phys::PhysicsConnector {
  %pythoncode{
    def setExport(self, *args, **kwargs):
      for key in kwargs:
        if key == "db_loc":
          self.setDBLocData(StringPairVector(self.tuplify(kwargs[key])))
        if key == "db_charge":
          self.setDBChargeData(StringPairVector(self.tuplify(kwargs[key])))
        if key == "potential":
          self.setElecPotentialData(StringVector2D(self.tuplify(kwargs[key])))
  }

  %pythoncode{
    def exportElecPotentialData(self, data_in):
      self.setElecPotentialData(StringVector2D(self.tuplify(data_in)))
  }
  %pythoncode{
    def exportDBChargeData(self, data_in):
      self.setDBChargeData(StringPairVector(self.tuplify(data_in)))
  }
  %pythoncode{
    def exportDBLocData(self, data_in):
      self.setDBLocData(StringPairVector(self.tuplify(data_in)))
  }
  %pythoncode{
    def tuplify(self, data):
      if hasattr(data,'__iter__') and not hasattr(data, "strip"):
        return tuple(self.tuplify(i) for i in data)
      else:
        return str(data)
  }
}

%extend phys::DBCollection {
  phys::DBIterator __iter__() {
    phys::DBIterator iter = $self->begin();
    iter.setCollection($self);
    return iter;
  }
}

%extend phys::DBIterator
{
  phys::DBDot *__iter__() {
    return &***($self);
  }

  phys::DBDot *__next__() {
    if (*($self) == $self->collection->end()) {
      //PyErr_SetString(PyExc_StopIteration,"End of list");
      //PyErr_SetNone(PyExc_StopIteration);
      return NULL;
    }
    phys::DBDot *db = &***($self);
    $self->operator++();
    return db;
  }
}