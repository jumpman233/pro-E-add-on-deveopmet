// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#ifdef _DEBUG
#pragma comment(linker,"\"/manifestdependency:type='Win32' name='Microsoft.VC80.CRT'version='8.0.50608.0' processorArchitecture='X86' publicKeyToken='1fc8b3b9a1e18e3b'language='*'\"")
#endif

#include <ProUtil.h>
#include <ProAsmcomp.h>
#include <ProMenubar.h>
#include <ProSkeleton.h>
#include <ProFeature.h>
#include <ProSolid.h>
#include <ProToolkit.h>
#include <ProToolkitDll.h>
#include <ProElement.h>
#include <ProGeomitem.h>
#include <ProFeatForm.h>
#include <ProFeatType.h>
#include <ProModFeat.h>
#include <ProStdSection.h>
#include <ProToolkitErrors.h>
#include <ProModelitem.h>
#include <ProWindows.h>
#include <ProMessage.h>
#include <ProDtmPln.h>
#include <ProChamfer.h>
#include <ProCsys.h>
#include <ProAxis.h>
#include <ProCsysdata.h>
#include <ProUtil.h>
#include <ProRelset.h>
#include <ProParameter.h>
#include <ProMdl.h>
#include <ProCore.h>
#include <ProSurface.h>
#include <ProSelbuffer.h>
#include <ProDataShareFeat.h>
#include <ProExtdata.h>
#include <ProLayer.h>
#include <prodev_light.h>
#include <Prorefer.h>
#include <select3d.h>
#include <pd_prototype.h>
#include <ProQuilt.h>
#include <ProIntf3Dexport.h>
#include <ProMenu.h>
#include <ProUdf.h>
#include <ProEdge.h>
#include <ProPattern.h>
#include <ProAssembly.h>
#include "ProToolkit.h"
#include "ProFeature.h"
#include "ProElemId.h"
#include "ProExtrude.h"
#include "ProModFeat.h"
#include "ProStdSection.h"
#include "ProElement.h"
#include "ProElempath.h"
#include "ProFeatType.h"
#include "ProFeatForm.h"
#include "ProSelection.h"
#include "ProSection.h"
#include "ProDtmCsys.h"
#include "ProToolkit.h"
#include "ProElemId.h"
#include "ProStdSection.h"
#include "ProElement.h"
#include "ProFeatType.h"
#include "ProFeatForm.h"
#include "ProSelection.h"
#include "ProHole.h"
#include <ProUIDialog.h>

#include <Shlwapi.h>
#include <vector>
using namespace std;

#include "resource.h"