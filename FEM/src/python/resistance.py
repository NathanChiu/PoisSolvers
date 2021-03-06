import numpy as np
import dolfin
import itertools
import networkx as nx
import res_graph
import scipy.interpolate

class ElectrodeDict:
    def __init__(self):
        self.dict = {} #start with empty dictionary

    def __getitem__(self, key):
        if key in self.dict:
            return self.dict[key]
        else:
            raise KeyError(key)

    def addKeyValue(self, key, value):
        if key in self.dict:
            self.dict[key].append(value)
        else:
            self.dict[key] = [value]

class ResistanceEstimator():
    def __init__(self, t = None, r = None,):
        self.dir = ""
        self.resistances = {}
        # self.material = ""
    #Sets two lists as the dataset, combining them into a dictionary.
    #If no arguments are provided, uses cryogenic data for cobalt.
    def setMaterialData(self, material="", t=None, r=None):
        #There was data given, use that instead
        if t != None and r != None:
            self.temps = t
            self.resistivities = r
        else:
            if material == "cobalt":
            #Otherwise use data from White and Woods, 1959
                self.temps = [10,15,20,25,30, \
                         40,50,60,70,80, \
                         90,100,120,140,160, \
                         180,200,220,250,273,295] #Kelvin
                self.resistivities = [0.0901,0.0917,0.0956,0.103,0.116, \
                                 0.161,0.234,0.339,0.469,0.629, \
                                 0.809,0.999,1.409,1.869,2.349, \
                                 2.839,3.319,3.809,4.589,5.239,5.889] #E6 ohm cm
            elif material == "copper":
                self.temps = [4.2, 15, 25, 25, 30, 40, \
                              50, 60, 70, 80, 90, \
                              100, 120, 140, 160, 180, \
                              200, 220, 250, 273, 295]
                self.resistivities = [0.0010154658, 0.00287, 0.0035, 0.0052, 0.0090, 0.0247, \
                                      0.0527, 0.0977, 0.1557, 0.2177, 0.2827, \
                                      0.3527, 0.4927, 0.6377, 0.7777, 0.9227, \
                                      1.0627, 1.2027, 1.4027, 1.5527, 1.7027]

    def getInterpolant(self, deg = None):
        self.interp = scipy.interpolate.interp1d(self.temps,self.resistivities)

    #Approximate
    def approxRes(self, x):
        print(self.interp(x))
        return self.interp(x)

    def buildElecDict(self):
        # Empty dictionary for electrodes
        self.elec_dict = ElectrodeDict()
        # Add all the electrodes into the dictionary, binned by net ID.
        for elec in self.elec_list:
            #Give each elec an arbitrary id
            elec.id = self.elec_list.index(elec)
            self.elec_dict.addKeyValue(elec.net, elec)

    def createResGraph(self, temp):
        # self.setMaterial()
        self.buildElecDict()
        self.res_graph = res_graph.ResGraph(self.elec_dict, self.elec_list, self.dir, self.approxRes(temp))

    def getResistances(self, temp):
        if self.mode == "res" or self.mode == "ac":
            self.createResGraph(temp)
            self.resistances = self.res_graph.getCalculatedResistances()
