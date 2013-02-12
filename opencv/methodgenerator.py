# -*- coding: utf-8 -*-

import datatype
import document
import package
import cvtype

class ArgumentVisitor(object):
    def visitInput(self, inputArg):
        pass
        
    def visitParameter(self, parameter):
        pass
        
    def visitNumericParameter(self, numericParameter):
        pass
        
    def visitConstant(self, const):
        pass
        
    def visitEnumParameter(self, enumParameter):
        pass
        
    def visitRefInput(self, refInput):
        pass
        
    def visitAllocation(self, allocation):
        pass
        
    def visitOutput(self, output):
        pass
        
    def visitSize(self, size):
        pass
        
        
class MethodGenerator(ArgumentVisitor):
    p = None
    m = None
    doc = None
    
    def save(self, package, method, printResult):
        self.p = package
        self.m = method
        self.doc = document.Document()
        
        self.generate()
        
        if printResult:
            print self.doc.string()
            
class OpHeaderGenerator(MethodGenerator):
    """
    >>> p = package.Package("imgproc", 0, 0, 1)
    >>> p.name = "OpenCV image processing"
    >>> m = package.Method("medianBlur")
    >>> arg1 = package.Argument("src", "Source", cvtype.Mat(), datatype.Image())
    >>> arg2 = package.Argument("dst", "Destination", cvtype.Mat(), datatype.Image())
    >>> arg3 = package.NumericParameter("ksize", "Kernel size", cvtype.Int(), datatype.UInt32())
    >>> opt = package.Option("manual")
    >>> opt.args.extend([package.Input(arg1, True), package.Output(arg2), arg3])
    >>> m.options.append(opt)
    >>> g = OpHeaderGenerator()
    >>> g.save(p, m, True)
    <BLANKLINE>
    """
    params = set()
    
    def generate(self):
        for opt in self.m.options:
            for arg in opt.args:
                arg.accept(self)
                
        for p in self.params:
            self.doc.line(p)
        
        with file("{0}.h".format(self.m.ident.className()), "w") as f:
            f.write(self.doc.string())
    
    def visitParameter(self, parameter):
        self.params.add(parameter.ident.attribute())
        
    def visitNumericParameter(self, parameter):
        self.params.add(parameter.ident.attribute())
            
class OpImplGenerator(MethodGenerator):
    
    def generate(self):
        
        with file("{0}.cpp".format(self.m.ident.className()), "w") as f:
            f.write(self.doc.string())
    
    def visitParameter(self, parameter):
        self.params.add(parameter.ident.attribute())
        
            
if __name__ == "__main__":
    import doctest
    doctest.testmod()     