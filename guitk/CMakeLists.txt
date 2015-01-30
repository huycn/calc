set (GUITK_INCLUDE
	"${CMAKE_CURRENT_SOURCE_DIR}/core"
	"${CMAKE_CURRENT_SOURCE_DIR}/widgets"
	CACHE INTERNAL "")

if (MSVC)
	add_definitions (
#		-D_SCL_SECURE_NO_WARNINGS
#		-D_CRT_SECURE_NO_WARNINGS
#		-D_CRT_NONSTDC_NO_WARNINGS
#		-D_VARIADIC_MAX=10
		-DNOMINMAX
#		-wd4503							# decorated name length exceeded
	)
endif()

include_directories (
	${GUITK_INCLUDE}
)

set (GUITK_CORE_FILES
	core/gkException.h
	core/gkPoint.h
	core/gkRect.h
	core/gkString.h
	core/gkString.cpp
)

set (GUITK_WIDGETS_FILES
	widgets/gkComboBox.h
	widgets/gkComboBox.cpp
	widgets/gkControl.h
	widgets/gkControl.cpp
	widgets/gkDialog.h
	widgets/gkDialog.cpp
	widgets/gkFrameWindow.h
	widgets/gkFrameWindow.cpp
	widgets/gkMainWindow.h
	widgets/gkMainWindow.cpp
	widgets/gkProgressBar.h
	widgets/gkProgressBar.cpp
	widgets/gkResource.h
	widgets/gkSplitter.h
	widgets/gkSplitter.cpp
	widgets/gkStatusBar.h
	widgets/gkStatusBar.cpp
	widgets/gkTextEdit.h
	widgets/gkTextEdit.cpp
	widgets/gkWindow.h
	widgets/gkWindow.cpp
	widgets/gkWindowUtil.h
)

source_group ("Source Files\\core" FILES ${GUITK_CORE_FILES})
source_group ("Source Files\\widgets" FILES ${GUITK_WIDGETS_FILES})

add_library (guitk
	${GUITK_CORE_FILES}
	${GUITK_WIDGETS_FILES}
)
