// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchmenu;

public class SearchWidgetViewJniMethods
{
	public static native void OnSearchResultsCleared(long nativeCallerPointer);
	public static native void OnSearchResultSelected(long nativeCallerPointer, int index);
}
