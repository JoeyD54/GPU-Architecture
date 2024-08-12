REM
REM Keenan's Hack to remove intermediate files
REM Designed to work for C++ or C# visual studio projects
REM
REM If you find a way to enhance, 
REM please return updates to ekeenan2@cdm.depaul.edu
REM

REM cleanup libraries before releasing to students

del /F .\File\src\*.cpp

del /F .\Math\src\*.cpp

del /F .\Math_2.0\src\*.cpp

del /F .\Math_3.0\src\*.cpp

del /F .\PCSTree\src\*.cpp


del /F .\Manager\src\*.cpp


