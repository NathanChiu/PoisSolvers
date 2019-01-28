 # @author:   Nathan
 # @created:  2018.08.23
 # @editted:  2017.08.23 - Nathan
 # @license:  GNU LGPL v3
 #
 # @desc:     Class definition for physics engine

import mesh_writer_3D as mw
import numpy as np
import os
import subdomains as sd
import dolfin
import sys
import helpers
import subprocess
import matplotlib.pyplot as plt
import matplotlib.colors as clrs
from PIL import Image

class Plotter():
    #Constructor
    def __init__(self):
        pass

    def saveAxesPotential(self,X,Y,Z,file_name):
        fig = plt.figure() #create a new figure
        plt.gca().invert_yaxis() # siqad has +x going right, +y going down
        max_val = np.max(np.abs(Z))
        # pin the colour scale extremes to +/- max value.
        norm = clrs.Normalize(vmin=-max_val, vmax=max_val)
        # set the colour map to use red/blue scheme
        plt.pcolormesh(X,Y,Z,norm=norm,cmap=plt.cm.get_cmap('RdBu_r'))
        cbar = plt.colorbar()
        cbar.set_label("Potential (V)")
        # get nice round numbers close to the y graduation values
        locs, labels = plt.yticks()
        labels = []
        for loc in locs:
            labels += [str(int(round(loc/10, 2)))]
        plt.yticks(locs, labels)        #replace the labels
        #do the same for x graduation values
        locs, labels = plt.xticks()
        labels = []
        for loc in locs:
            labels += [str(int(round(loc/10, 2)))]
        plt.xticks(locs, labels)
        plt.xlabel("X (nm)") #set label text
        plt.ylabel("Y (nm)")
        #save the picture to file, and close
        plt.savefig(file_name, bbox_inces="tight", pad_inches=0)
        plt.close(fig)

    def saveGrad(self,X,Y,Z,index,file_name):
        fig = plt.figure(frameon=False) #create a new figure
        plt.gca().invert_yaxis() # siqad has +x going right, +y going down
        Zgrad = np.gradient(Z) #get the gradient. Zgrad[0] is x direction, Zgrad[1] is y direction
        maxval = np.max(np.abs(Zgrad[index]))
        norm = clrs.Normalize(vmin=-maxval, vmax=maxval)
        #use the normalized values to obtain a suitable colour mapping.
        plt.pcolormesh(X,Y,Zgrad[index],norm=norm,cmap=plt.cm.get_cmap('RdBu_r'))
        cbar = plt.colorbar()
        cbar.set_label("E field (V/m)")
        plt.subplots_adjust(left=0, right=1, top=1, bottom=0)
        plt.savefig(file_name)
        plt.close(fig)

    def savePotential(self, X, Y, Z, step, file_name):
        fig = plt.figure(frameon=False)
        plt.gca().invert_yaxis()
        plt.axis('off')
        maxval = np.max(np.abs(Z))
        norm = clrs.Normalize(vmin=-maxval, vmax=maxval)
        plt.pcolormesh(X,Y,Z,norm=norm,cmap=plt.cm.get_cmap('RdBu_r'))
        plt.subplots_adjust(left=0, right=1, top=1, bottom=0)
        plt.savefig(file_name)
        plt.close(fig)

    def create2DSlice(self, u, depth, resolution, bounds):
        x = np.linspace(bounds['xmin'], bounds['xmax'], resolution)
        y = np.linspace(bounds['ymin'], bounds['ymax'], resolution)
        X, Y = np.meshgrid(x, y)
        z = np.array([u(i, j, bounds['dielectric']+depth) for j in y for i in x])
        Z = z.reshape(resolution, resolution)
        return X, Y, Z, resolution, resolution

    def makeGif(self, mode, dir, dir_files):
        if mode == "clock":
            images = []
            image_files = []
            for file in dir_files:
                if file.startswith("SiAirBoundary"):
                    image_files.append(os.path.join(dir, file))
            image_files.sort()
            for image_name in image_files:
                images.append(Image.open(image_name))
            images[0].save(os.path.join(dir, "SiAirBoundary.gif"),
                       save_all=True,
                       append_images=images[1:],
                       delay=0.5,
                       loop=0)