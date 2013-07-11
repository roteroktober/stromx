# -*- coding: utf-8 -*-
"""
Created on Sat Jan 19 17:00:37 2013

@author: matz
"""

class CvType(object):
    """
    Represents an OpenCV data type.
    """
    def typeId(self):
        """
        Returns the name of the type, e.g. "bool".
        """
        raise NotImplementedError()
        
    def cast(self, src):
        """
        Returns a conversion of the input variable to the type, e.g.
        "bool(src)".
        """
        return "{0}({1})".format(self.typeId(), src)
        
class Bool(CvType):
    """
    Native C++ bool type.
    """
    def typeId(self):
        return "bool"
        
class Int(CvType):
    """
    Native C++ int type.
    """
    def typeId(self):
        return "int"
        
class Float64(CvType):
    """
    Native C++ double type.
    """
    def typeId(self):
        return "double"
        
class Mat(CvType):
    """
    OpenCV cv::Mat type.
    """
    def typeId(self):
        return "cv::Mat"
    
    def cast(self, src):
        return "cvsupport::getOpenCvMat({0})".format(src)
        
if __name__ == "__main__":
    import doctest
    doctest.testmod()
    