#set ($NAMESPACE = $DIR_PATH.replace("/", "::"))
#if ($NAMESPACE.startsWith("src::"))
    #set ($NAMESPACE = $NAMESPACE.replaceFirst("src::", ""))
#end
#set ($NAMESPACE = ${PROJECT_NAME} + "::" + ${NAMESPACE})
#set ($GUARD = $NAMESPACE.replace("::","_") + "_" + $FILE_NAME.replace(".", "_"))
#set ($GUARD = $GUARD.toUpperCase())