# there are 2 files in the main branch - firstAna.cc and firstAna.cc.backup. Former is the executable file, latter is the copy I made as a result of many stupid decisions. 
go to your terminal (assuming you have already installed the ROOT Framework and are using Linux). write the line:
root -l firstAna.cc, 
and after a long time of waiting, when the program is finally done, simply write:
new TBrowser
this way, you will be able to access all histograms included in the code. Browse through them, and have fun investigating the Z boson!
