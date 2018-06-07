%module siqadconn
%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>
%include <exception.i>

%{
#include "siqadconn.h"
%}

%include "siqadconn.h"

namespace std {
    %template(IntVector) vector<int>;
    %template(StringPair) pair<string, string>;
    %template(StringPairVector) vector< pair<string, string> >;
    %template(StringVector) vector<string>;
    %template(StringVector2D) vector< vector<string> >;
    %template(StringMap) map< string, string >;
    %template(LayerVector) vector<phys::Layer>;
}

%{
#define SWIG_FILE_WITH_INIT
#define SWIG_PYTHON_2_UNICODE
%}


%feature("shadow") phys::DBIterator::__next__() %{
  def __next__(self):
    db = $action(self)
    if db == None:
      raise StopIteration
    else:
      return db
%}

%feature("shadow") phys::ElecIterator::__next__() %{
  def __next__(self):
    elec = $action(self)
    if elec == None:
      raise StopIteration
    else:
      return elec
%}

%extend phys::SiQADConnector {
  %pythoncode{
    def export(self, *args, **kwargs):
      for key in kwargs:
        self.setExport(key, StringVector2D(self.tuplify(kwargs[key])))
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

%extend phys::ElectrodeCollection {
  phys::ElecIterator __iter__() {
    phys::ElecIterator iter = $self->begin();
    iter.setCollection($self);
    return iter;
  }
}

%extend phys::ElecIterator
{
  phys::Electrode *__iter__() {
    return &***($self);
  }

  phys::Electrode *__next__() {
    if (*($self) == $self->collection->end()) {
      //PyErr_SetString(PyExc_StopIteration,"End of list");
      //PyErr_SetNone(PyExc_StopIteration);
      return NULL;
    }
    phys::Electrode *elec = &***($self);
    $self->operator++();
    return elec;
  }
}
