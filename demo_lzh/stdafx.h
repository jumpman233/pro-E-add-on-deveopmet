// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
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