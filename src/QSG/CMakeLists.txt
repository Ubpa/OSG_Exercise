macro(QSG_SETUP TARGET_PARTNAME STR_TARGET_SOURCES)
	set( TARGET_NAME ${TARGET_PREFIX}${TARGET_PARTNAME})
	string(REPLACE " " ";" LIST_TARGET_SOURCES ${STR_TARGET_SOURCES})
	add_executable( ${TARGET_NAME} ${LIST_TARGET_SOURCES})
	SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

	target_link_libraries( ${TARGET_NAME}
		OpenThreadsd.lib
		osgViewerd.lib
		opengl32.lib
		osgGAd.lib
		osgTextd.lib
		osgDBd.lib
		osgUtild.lib
		osgd.lib
		zlibd.lib
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
endmacro(QSG_SETUP TARGET_NAME TARGET_SOURCES)

add_subdirectory (01_Simple)
add_subdirectory (02_Viewer)
add_subdirectory (03_State)
add_subdirectory (04_TextureMapping)
add_subdirectory (05_Lighting)
add_subdirectory (06_Text)
add_subdirectory (07_Callback)
add_subdirectory (08_FindNode)
add_subdirectory (09_Picking)