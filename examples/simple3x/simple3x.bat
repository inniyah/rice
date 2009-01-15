if X%1X==XX       goto end
if X%1X==XBEFOREX goto before
if X%1X==XAFTERX  goto after

:before
copy simple3x.lnk rice.lnk
copy simple3x.cod rice.cod

:after
del rice.lnk
del rice.cod

:end

