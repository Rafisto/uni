import sys
import os
import struct
import numpy as np

class Image:
    def __init__(self, filename):
        with open(filename, "rb") as f:
            header = f.read(18)
            (
                id_length,
                color_map_type,
                image_type,
                color_map_origin,
                color_map_length,
                color_map_depth,
                x_origin,
                y_origin,
                width,
                height,
                pixel_depth,
                image_descriptor
            ) = struct.unpack("<BBBHHBHHHHBB", header)
            
            if id_length:
                f.read(id_length)

            if color_map_type:
                f.read(color_map_length * (color_map_depth // 8))

            bytes_per_pixel = pixel_depth // 8
            image_size = width * height * bytes_per_pixel
            pixel_data = f.read(image_size)

            pixels = []
            for i in range(0, len(pixel_data), bytes_per_pixel):
                if bytes_per_pixel == 3:
                    b, g, r = pixel_data[i:i+3]
                    pixels.append(np.array([r, g, b]))
                else:
                    raise ValueError("Unsupported pixel depth.")

        self.image_descriptor = image_descriptor
        self.width = width
        self.height = height
        self.pixel_depth = pixel_depth
        self.pixels = pixels
        
    def get_pixels(self):
        return self.pixels
    
    def set_pixels(self, pixels):
        self.pixels = pixels
    
    def save(self, filename):
        with open(filename, "wb") as f:
            id_length = 0
            color_map_type = 0
            image_type = 2 
            color_map_origin = 0
            color_map_length = 0
            color_map_depth = 0
            x_origin = 0
            y_origin = 0
            width = self.width
            height = self.height
            pixel_depth = self.pixel_depth
            image_descriptor = self.image_descriptor
            
            header = struct.pack(
                "<BBBHHBHHHHBB",
                id_length,
                color_map_type,
                image_type,
                color_map_origin,
                color_map_length,
                color_map_depth,
                x_origin,
                y_origin,
                width,
                height,
                pixel_depth,
                image_descriptor
            )
            f.write(header)
            
            for i in range(0,len(self.pixels),3):
                if pixel_depth == 24:
                    r, g, b = self.pixels[i:i+3]
                    f.write(struct.pack("BBB", b, g, r))
                else:
                    raise ValueError("Unsupported pixel depth.")
