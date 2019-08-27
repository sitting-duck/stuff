main();

function main() {

LogMessage( "Starting test: FindPluginInSystemInfo" );

var fileLog = new File( "~/Desktop/FindPluginInSystemInfo.log" );
fileLog.open( "w" );
var errors = 0;
var sysInfo = app.systemInformation;
var failStart = sysInfo.search( "Plug-ins that failed to load:" );
if ( failStart == -1 ) {
    errors++;
    fileLog.writeln( "No failed to load found" );
}
var failEnd = sysInfo.search( "Extensions:");
if ( failEnd == -1 ) {
    errors++;
    fileLog.writeln( "No flash found" );
}
if ( failEnd < failStart ) {
    errors++;
    fileLog.writeln( "failEnd < failStart" );
}
   
// TODO double check the statistics version, "Generic Plug-in" and 3dsimulator 
// one plug-in could have more than one entry, statistics and SelectoramaShape
// some plug-ins don't show up, see above TODO to confirm
var pluginList = [ 
 "AutomationFilter",     "ColorMunger",         "Dissolve",    "Getter", 
 "GradientImport",       "Hidden",              "History",     "LayerFormat", 
 "Listener",             "Measurement Sample",  "NearestBase", "Outbound", 
 "Poor Man's Type Tool", "Propetizer",          "Selectorama", "Shape", 
 "SimpleFormat",         "Entropy",             "Kurtosis",    "Maximum",
 "Mean",                 "Median",              "Minimum",     "Range", 
 "Skewness",             "Standard Deviation",  "Summation",   "Variance", 
 "TextAuto",             "TextFormat" ];
                   
if ( $.os.search(/windows/i) != -1 )
	pluginList.push( "MFC PlugIn" );

var pluginIndex = [];

for ( var i = 0; i < pluginList.length; i++ ) {
    pluginIndex[i] = sysInfo.search( pluginList[i] );
    // $.writeln( pluginList[i] + " = " + pluginIndex[i] );
    if ( pluginIndex[i] == -1 ) {
        errors++;
        fileLog.writeln( "Plug in not found: " + pluginList[i] );
    }
    else if ( pluginIndex[i] > failStart && pluginIndex[i] < failEnd ) {
        errors++;
        fileLog.writeln( "pluginIndex[i] > failStart && pluginIndex[i] < failEnd " +  pluginList[i] );
    }
}

fileLog.close();

if (errors) {
	fileLog.execute();
}

var result = errors == 0 ? ' PASS' : ' FAIL';

if (typeof gHarness == "undefined" || gHarness.showAlerts )
    alert(result);

return result;
}

function LogMessage( inMessage ) {
  if ( BridgeTalk.isRunning( "estoolkit" ) )
    $.writeln( inMessage );
}


// end FindPluginInSystemInfo.jsx
