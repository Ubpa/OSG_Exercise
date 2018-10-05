set(TARGET_PARTNAME 05_Lighting)
#多个源文件用 [空格] 分割
set(STR_TARGET_SOURCES "LightingMain.cpp LightingSG.cpp")
QSG_SETUP(${TARGET_PARTNAME} ${STR_TARGET_SOURCES})