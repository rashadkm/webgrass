test -r ~/.alias && . ~/.alias
PS1='GRASS 7.0.5svn (newLocation):\w > '
grass_prompt() {
	LOCATION="`g.gisenv get=GISDBASE,LOCATION_NAME,MAPSET separator='/'`"
	if test -d "$LOCATION/grid3/G3D_MASK" && test -f "$LOCATION/cell/MASK" ; then
		echo [2D and 3D raster MASKs present]
	elif test -f "$LOCATION/cell/MASK" ; then
		echo [Raster MASK present]
	elif test -d "$LOCATION/grid3/G3D_MASK" ; then
		echo [3D raster MASK present]
	fi
}
PROMPT_COMMAND=grass_prompt
export GRASS_GNUPLOT="gnuplot -persist"
export GRASS_PROJSHARE=/usr/share/proj
export GRASS_ADDON_BASE=/home/mayank/.grass7/addons
export GRASS_HTML_BROWSER=xdg-open
export GRASS_PYTHON=python
export GRASS_VERSION=7.0.5svn
export GRASS_PAGER=more
export PATH="/usr/local/grass-7.0.5svn/bin:/usr/local/grass-7.0.5svn/scripts:/home/mayank/.grass7/addons/bin:/home/mayank/.grass7/addons/scripts:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games"
export HOME="/home/mayank"
