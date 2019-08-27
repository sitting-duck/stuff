/*
	File: statistics.r

	Copyright (c) 2006, Adobe Systems Incorporated.
	All rights reserved.

	Rez source file for image stack statistics.


DONE
	Mean
	Summation
	Maximum
	Minimum
	Variance
	Standard Deviation
	Skewness
	Kurtosis
	Range = (max - min)
	Median
	Entropy


*/

/*********************************************************************/

#define IDD_ABOUT       16000
#define IDD_PARAM     	16001

/*********************************************************************/
/* Defines required for include files */

#define plugInName						"Statistics"

/*********************************************************************/

#include "PIDefines.h"

#ifdef __PIMac__
	#include <Carbon.r>
	#include "PIGeneral.r"
	#include "statisticsRes.h"
	#include "PIUtilities.r"
#elif defined(__PIWin__)
	#define Rez
	#include "statisticsRes.h"
	#include "PIGeneral.h"
	#include "PIUtilities.r"
#endif

#include "PIActions.h"

/*********************************************************************/

#define ourClassID1						'avrS'
#define ourClassID2						'sumS'
#define ourClassID3						'minS'
#define ourClassID4						'maxS'
#define ourClassID5						'medS'
#define ourClassID6						'varS'
#define ourClassID7						'stdS'
#define ourClassID8						'skeS'
#define ourClassID9						'kurS'
#define ourClassID10					'ranS'
#define ourClassID11					'entS'
#define ourEventID						typeNull // must be this

#if TARGET_MAC_OS
#include "VersionStrings.h"
#endif
// #include "PIVersion.r"

/*********************************************************************/

resource 'PiPL' (ResourceID, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Mean SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/MeanSDK=Mean SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Mean SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "MEAN_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "MEAN_ENTRY" },
			#else
				CodeWin32X86 { "MEAN_ENTRY" },
			#endif
		#endif
		
   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID1, ourEventID, ResourceID, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+1, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Summation SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/SummationSDK=Summation SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Summation SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "SUM_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "SUM_ENTRY" },
			#else
				CodeWin32X86 { "SUM_ENTRY" },
			#endif
		#endif
		
   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID2, ourEventID, ResourceID+1, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+2, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Minimum SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/MinimumSDK=Minimum SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Minimum SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "MIN_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "MIN_ENTRY" },
			#else
				CodeWin32X86 { "MIN_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID3, ourEventID, ResourceID+2, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+3, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Maximum SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/MaximumSDK=Maximum SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Maximum SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "MAX_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "MAX_ENTRY" },
			#else
				CodeWin32X86 { "MAX_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID4, ourEventID, ResourceID+3, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+4, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Median SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/MedianSDK=Median SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Median SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "MEDIAN_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "MEDIAN_ENTRY" },
			#else
				CodeWin32X86 { "MEDIAN_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID5, ourEventID, ResourceID+4, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+5, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Variance SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/VarianceSDK=Variance SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Variance SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "VAR_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "VAR_ENTRY" },
			#else
				CodeWin32X86 { "VAR_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID6, ourEventID, ResourceID+5, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+6, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Standard Deviation SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/StandardDeviationSDK=Standard Deviation SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Standard Deviation SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "STDDEV_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "STDDEV_ENTRY" },
			#else
				CodeWin32X86 { "STDDEV_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID7, ourEventID, ResourceID+6, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+7, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Skewness SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/SkewnessSDK=Skewness SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Skewness SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "SKEW_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "SKEW_ENTRY" },
			#else
				CodeWin32X86 { "SKEW_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID8, ourEventID, ResourceID+7, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+8, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Kurtosis SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/KurtosisSDK=Kurtosis SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Kurtosis SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "KURT_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "KURT_ENTRY" },
			#else
				CodeWin32X86 { "KURT_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID9, ourEventID, ResourceID+8, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+9, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Range SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/RangeSDK=Range SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Range SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "RANGE_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "RANGE_ENTRY" },
			#else
				CodeWin32X86 { "RANGE_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID10, ourEventID, ResourceID+9, "" },
		
		StackRenderer { },

		}
	};

/*********************************************************************/

resource 'PiPL' (ResourceID+10, purgeable)
	{
		{
		Kind { Acquire },

		Name { "Entropy SDK" },

		ZStringName { "$$$/AdobePlugin/PIPLInfo/PluginName/EntropySDK=Entropy SDK" },
		
		Version { (latestAcquireVersion << 16) | latestAcquireSubVersion },

		Component { ComponentNumber, "Entropy SDK" },
		
		#ifdef __PIMac__
			CodeMacIntel64 { "ENTROPY_ENTRY" },
		#else
			#if defined(_WIN64)
				CodeWin64X86 { "ENTROPY_ENTRY" },
			#else
				CodeWin32X86 { "ENTROPY_ENTRY" },
			#endif
		#endif

   		RequiredHost { '8BIM' },
   		
		PlugInMaxSize { 2000000, 2000000 },

		/* class ID, event ID, aete ID, uniqueString */
		HasTerminology { ourClassID11, ourEventID, ResourceID+10, "" },
		
		StackRenderer { },

		}
	};


/*********************************************************************/
	
/* Scripting resource */

resource 'aete' (ResourceID, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/MeanSDK=Mean SDK",
			ourClassID1,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};


/*********************************************************************/
	
/* Scripting resource */

resource 'aete' (ResourceID+1, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/SummationSDK=Summation SDK",
			ourClassID2,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};


/*********************************************************************/
	
/* Scripting resource */

resource 'aete' (ResourceID+2, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/MinimumSDK=Minimum SDK",
			ourClassID3,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};


/*********************************************************************/
	
/* Scripting resource */

resource 'aete' (ResourceID+3, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/MaximumSDK=Maximum SDK",
			ourClassID4,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+4, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/MedianSDK=Median SDK",
			ourClassID5,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+5, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/VarianceSDK=Variance SDK",
			ourClassID6,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+6, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/StandardDeviationSDK=Standard Deviation SDK",
			ourClassID7,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+7, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/SkewnessSDK=Skewness SDK",
			ourClassID8,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+8, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/KurtosisSDK=Kurtosis SDK",
			ourClassID9,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+9, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/RangeSDK=Range SDK",
			ourClassID10,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/

resource 'aete' (ResourceID+10, purgeable)
{
	1, 0, english, roman,
	{
		"$$$/AETE/Common/Photoshop=Photoshop",
		"",
		'PHTO',
		0,
		0,
		{},	/* events */
		{
			"$$$/AdobePlugin/statistics/EntropySDK=Entropy SDK",
			ourClassID11,
			"",
			{},
			{}, /* elements (not supported) */
		},
		{}, /* comparison ops (not supported) */
		{}	/* enums */
	}
};

/*********************************************************************/