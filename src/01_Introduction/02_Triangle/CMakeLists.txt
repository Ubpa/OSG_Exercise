set( TARGET_NAME ${TARGET_PREFIX}02_Triangle)
add_executable( ${TARGET_NAME} main.cpp )
SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

target_link_libraries( ${TARGET_NAME}
	OpenThreadsd.lib
	osgd.lib
	osgUtild.lib
	osgDBd.lib
	osgGAd.lib
	osgTextd.lib
	osgViewerd.lib
	
	zlibd.lib
	opengl32.lib
	kernel32.lib
	user32.lib
	gdi32.lib
	winspool.lib
	shell32.lib
	ole32.lib
	oleaut32.lib
	uuid.lib
	comdlg32.lib
	advapi32.lib
)
install (TARGETS ${TARGET_NAME} DESTINATION bin/${FOLDER_NAME})
