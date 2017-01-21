// Demo.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "demo_lzh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// Cdemo_lzhApp

BEGIN_MESSAGE_MAP(Cdemo_lzhApp, CWinApp)
END_MESSAGE_MAP()


// Cdemo_lzhApp 构造

Cdemo_lzhApp::Cdemo_lzhApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 Cdemo_lzhApp 对象

Cdemo_lzhApp theApp;


// Cdemo_lzhApp 初始化

BOOL Cdemo_lzhApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

static uiCmdAccessState AccessDefault(uiCmdAccessMode access_mode)
{
	return(ACCESS_AVAILABLE);
}
int Menu1(uiCmdCmdId command,uiCmdValue * p_value,void * p_push_command_data)
{
	int i = 0;
	ProUIDialogCreate("demo","angle");
	ProUIDialogActivate("demo",&i);
	//创建模型
	ProMdl tpl;
	ProMdlLoad(L"D:\\Demo\\Publish\\start.prt",PRO_MDL_PART,PRO_B_FALSE,&tpl);

	ProMdl mdl;
	ProMdlCopy(tpl,L"demo.prt",&mdl);

	ProMdlDisplay(mdl);
	ProMdlErase(tpl);

	return 0;
}

int ProDatumPlaneCreate(ProSelection offset_surface,double       offset_dist)
{
	ProError		status;
	ProElement		elem_tree,elem_ftype,elem_consts,elem_offset;
	ProElement		elem_const_type,elem_offset_ref,elem_offset_dist;
	ProValueData	value_data;
	ProValue		value;
	ProModelitem    surf_modelitem,model_modelitem;
	ProSelection	mdl_sel;
	ProFeature		feature;
	ProErrorlist	errors;
	status = ProElementAlloc (PRO_E_FEATURE_TREE,&elem_tree);
	status = ProElementAlloc (PRO_E_FEATURE_TYPE,&elem_ftype);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_FEAT_DATUM;
	ProValueAlloc(&value);
	ProValueDataSet(value,&value_data);
	ProElementValueSet(elem_ftype,value);
	ProElemtreeElementAdd(elem_tree,NULL,elem_ftype);
	status = ProElementAlloc (PRO_E_DTMPLN_CONSTRAINTS,&elem_consts);
	ProElemtreeElementAdd(elem_tree,NULL,elem_consts);
	status = ProElementAlloc (PRO_E_DTMPLN_CONSTRAINT,&elem_offset);
	status = ProElemtreeElementAdd(elem_consts,NULL,elem_offset);
	status = ProElementAlloc (PRO_E_DTMPLN_CONSTR_TYPE,&elem_const_type);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_DTMPLN_OFFS;
	ProValueAlloc(&value);
	ProValueDataSet(value,&value_data);
	ProElementValueSet(elem_const_type,value);

	status = ProElemtreeElementAdd(elem_offset,NULL,elem_const_type);
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTR_REF,&elem_offset_ref);
	value_data.type = PRO_VALUE_TYPE_SELECTION;
	value_data.v.r = offset_surface;
	ProValueAlloc(&value);
	ProValueDataSet(value,&value_data);
	ProElementValueSet(elem_offset_ref,value);

	status = ProElemtreeElementAdd(elem_offset,NULL,elem_offset_ref);
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTR_REF_OFFSET,&elem_offset_dist);
	value_data.type = PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d = offset_dist;
	ProValueAlloc(&value);
	ProValueDataSet(value,&value_data);
	ProElementValueSet(elem_offset_dist,value);

	status = ProElemtreeElementAdd(elem_offset,NULL,elem_offset_dist);
	status = ProSelectionModelitemGet(offset_surface,&surf_modelitem);
	status = ProMdlToModelitem(surf_modelitem.owner,&model_modelitem);
	status = ProSelectionAlloc(NULL,&model_modelitem,&mdl_sel);
	status = ProFeatureCreate(mdl_sel,elem_tree,NULL,0,&feature,&errors);
	status = ProElementFree(&elem_tree);
	status = ProSelectionFree(&mdl_sel);

	return (status);
}

int Menu2(uiCmdCmdId command,uiCmdValue * p_value,void * p_push_command_data)
{
	//创建基准面
	ProError status;
	ProSelection*sel=NULL;
	int sel_num;
	status=ProSelect("sldface",1,NULL,NULL,NULL,NULL,&sel,&sel_num);
	ProDatumPlaneCreate(*sel,100);
	return 0;
}

ProError ProDemoGeneralCsysCreate()
{
	ProErrorlist		errors;
	ProMdl			model;
	ProModelitem		model_item;
	ProSelection		model_sel;
	ProFeature		feature;
	ProFeatureCreateOptions	opts[1];
	ProAsmcomppath		*p_comp_path=NULL;
	ProValue		value;
	ProError status;

	ProElement pro_e_feature_tree;
	ProElement pro_e_feature_type;
	ProElement pro_e_std_feature_name;
	ProElement pro_e_csys_origin_constrs;
	ProElement pro_e_csys_origin_constr;
	ProElement pro_e_csys_origin_constr_ref;
	ProElement pro_e_csys_offset_type;
	ProElement pro_e_csys_orientmoves;
	ProElement pro_e_csys_orientmove;
	ProElement pro_e_csys_orientmove_move_type;
	ProElement pro_e_csys_orientmove_move_val;
	ProElement pro_e_csys_orient_by_method;

	ProName wide_string;
	ProValueData value_data;
	ProSelection * p_select;
	int n_select;
	ProBoolean is_interactive = PRO_B_TRUE;


	
	status=ProElementAlloc(PRO_E_FEATURE_TREE,&pro_e_feature_tree);
	status=ProElementAlloc(PRO_E_FEATURE_TYPE,&pro_e_feature_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_FEAT_CSYS;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_feature_type,value);
	status=ProElemtreeElementAdd(pro_e_feature_tree,NULL,pro_e_feature_type);
	status=ProElementAlloc(PRO_E_STD_FEATURE_NAME,&pro_e_std_feature_name);
	ProStringToWstring(wide_string,"MY_CS0");
	value_data.type=PRO_VALUE_TYPE_WSTRING;
	value_data.v.w=wide_string;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_std_feature_name,value);
	status=ProElemtreeElementAdd(pro_e_feature_tree,NULL,pro_e_std_feature_name);
	status=ProElementAlloc(PRO_E_CSYS_ORIGIN_CONSTRS,&pro_e_csys_origin_constrs);
	status=ProElemtreeElementAdd(pro_e_feature_tree,NULL,pro_e_csys_origin_constrs);
	status=ProElementAlloc(PRO_E_CSYS_ORIGIN_CONSTR,&pro_e_csys_origin_constr);
	status=ProElemtreeElementAdd(pro_e_csys_origin_constrs,NULL,pro_e_csys_origin_constr);
	status=ProSelect("csys",1,NULL,NULL,NULL,NULL,&p_select,&n_select);
	if(n_select <= 0) return PRO_TK_GENERAL_ERROR;
	status=ProElementAlloc(PRO_E_CSYS_ORIGIN_CONSTR_REF,&pro_e_csys_origin_constr_ref);
	value_data.type=PRO_VALUE_TYPE_SELECTION;
	value_data.v.r=p_select[0];
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_origin_constr_ref,value);
	status=ProElemtreeElementAdd(pro_e_csys_origin_constr,NULL,pro_e_csys_origin_constr_ref);
	status=ProElementAlloc(PRO_E_CSYS_OFFSET_TYPE,&pro_e_csys_offset_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_OFFSET_CARTESIAN;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_offset_type,value);
	status=ProElemtreeElementAdd(pro_e_feature_tree,NULL,pro_e_csys_offset_type);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVES,&pro_e_csys_orientmoves);
	status=ProElemtreeElementAdd(pro_e_feature_tree,NULL,pro_e_csys_orientmoves);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE,&pro_e_csys_orientmove);
	status=ProElemtreeElementAdd(pro_e_csys_orientmoves,NULL,pro_e_csys_orientmove);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_TYPE,&pro_e_csys_orientmove_move_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENTMOVE_MOVE_OPT_ROT_X;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_type,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_type);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_VAL,&pro_e_csys_orientmove_move_val);
	value_data.type=PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d=0.000000;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_val,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE,&pro_e_csys_orientmove);
	status=ProElemtreeElementAdd(pro_e_csys_orientmoves,NULL,pro_e_csys_orientmove);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_TYPE,&pro_e_csys_orientmove_move_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENTMOVE_MOVE_OPT_ROT_Y;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_type,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_VAL,&pro_e_csys_orientmove_move_val);
	value_data.type=PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d=-90.000000;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_val,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE,&pro_e_csys_orientmove);
	status=ProElemtreeElementAdd(pro_e_csys_orientmoves,NULL,pro_e_csys_orientmove);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_TYPE,&pro_e_csys_orientmove_move_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENTMOVE_MOVE_OPT_ROT_Z;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_type,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_type);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_VAL,&pro_e_csys_orientmove_move_val);
	value_data.type=PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d=0.000000;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_val,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE,&pro_e_csys_orientmove);
	status=ProElemtreeElementAdd(pro_e_csys_orientmoves,NULL,pro_e_csys_orientmove);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_TYPE,&pro_e_csys_orientmove_move_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENTMOVE_MOVE_OPT_TRAN_X;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_type,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_type);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_VAL,&pro_e_csys_orientmove_move_val);
	value_data.type=PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d=100.000000;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_val,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE,&pro_e_csys_orientmove);
	status=ProElemtreeElementAdd(pro_e_csys_orientmoves,NULL,pro_e_csys_orientmove);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_TYPE,&pro_e_csys_orientmove_move_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENTMOVE_MOVE_OPT_TRAN_Y;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_type,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_type);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_VAL,&pro_e_csys_orientmove_move_val);
	value_data.type=PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d=200.000000;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_val,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE,&pro_e_csys_orientmove);
	status=ProElemtreeElementAdd(pro_e_csys_orientmoves,NULL,pro_e_csys_orientmove);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_TYPE,&pro_e_csys_orientmove_move_type);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENTMOVE_MOVE_OPT_TRAN_Z;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_type,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_type);
	status=ProElementAlloc(PRO_E_CSYS_ORIENTMOVE_MOVE_VAL,&pro_e_csys_orientmove_move_val);
	value_data.type=PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d=300.000000;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orientmove_move_val,value);
	status=ProElemtreeElementAdd(pro_e_csys_orientmove,NULL,pro_e_csys_orientmove_move_val);
	status=ProElementAlloc(PRO_E_CSYS_ORIENT_BY_METHOD,&pro_e_csys_orient_by_method);
	value_data.type=PRO_VALUE_TYPE_INT;
	value_data.v.i=PRO_CSYS_ORIENT_BY_SEL_CSYS_AXES;
	status=ProValueAlloc(&value);
	status=ProValueDataSet(value,&value_data);
	status=ProElementValueSet(pro_e_csys_orient_by_method,value);
	status=ProElemtreeElementAdd(pro_e_feature_tree,NULL,pro_e_csys_orient_by_method);
	status=ProMdlCurrentGet(&model);
	if(status!=PRO_TK_NO_ERROR) return (status);
	status=ProMdlToModelitem(model,&model_item);
	status=ProSelectionAlloc(p_comp_path,&model_item,&model_sel);

	opts[0]=PRO_FEAT_CR_DEFINE_MISS_ELEMS;
	status=ProFeatureCreate(model_sel,pro_e_feature_tree,opts,1,&feature,&errors);
	status=ProElementFree(&pro_e_feature_tree);
	return (status);
}

int Menu3(uiCmdCmdId command,uiCmdValue * p_value,void * p_push_command_data)
{
	//创建坐标系
	ProDemoGeneralCsysCreate();
	return 0;
}
ProError UserElemtreeElementAdd(ProElement parent_element,ProElement child_element,ProValueData
value_data)
{
	ProValue value;
	ProError status;
	
	status = ProValueAlloc (&value);
	status = ProValueDataSet (value,&value_data);
	status = ProElementValueSet (child_element,value);
	status = ProElemtreeElementAdd (parent_element,NULL,child_element);
	return (status);
}
ProError ProDemoHoleCreate()
{
	ProError status;
	ProElement feat_elemtree;
	ProElement elem_feattype;
	ProElement elem_featform;
	ProElement elem_hle_com;
	ProElement elem_hle_type_new;
	ProElement elem_diameter;
	ProElement elem_hole_std_depth;
	ProElement elem_hole_depth_to;
	ProElement elem_hole_depth_to_type;
	ProElement elem_hole_depth_from;
	ProElement elem_hole_depth_from_type;
	ProElement elem_hle_placement;
	ProElement elem_hle_prim_ref;
	ProElement elem_hle_pl_type;
	ProElement elem_hle_dim_ref1;
	ProElement elem_hle_dim_dist1;
	ProElement elem_hle_dim_ref2;
	ProElement elem_hle_dim_dist2;
	ProValueData value_data;
	ProSelection *p_selection;
	int n_selection;
	ProFeatureCreateOptions options[] = {PRO_FEAT_CR_DEFINE_MISS_ELEMS};
	ProFeature created_feature;
	ProErrorlist p_errors;
	ProMdl model;
	ProModelitem model_item;
	ProSelection model_selection;
	status = ProElementAlloc (PRO_E_FEATURE_TREE,&feat_elemtree);
	status = ProElementAlloc (PRO_E_FEATURE_TYPE,&elem_feattype);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_FEAT_HOLE;
	status = UserElemtreeElementAdd (feat_elemtree,elem_feattype,value_data);
	status = ProElementAlloc (PRO_E_FEATURE_FORM,&elem_featform);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_HLE_TYPE_STRAIGHT;
	status = UserElemtreeElementAdd (feat_elemtree,elem_featform,value_data);
	status = ProElementAlloc (PRO_E_HLE_COM,&elem_hle_com);
	status = ProElemtreeElementAdd (feat_elemtree,NULL,elem_hle_com);
	status = ProElementAlloc (PRO_E_HLE_TYPE_NEW,&elem_hle_type_new);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_HLE_NEW_TYPE_STRAIGHT;
	status = UserElemtreeElementAdd (elem_hle_com,elem_hle_type_new,value_data);
	status = ProElementAlloc (PRO_E_DIAMETER,&elem_diameter);
	value_data.type = PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d = 100.0;
	status = UserElemtreeElementAdd (elem_hle_com,elem_diameter,value_data);
	status = ProElementAlloc (PRO_E_HOLE_STD_DEPTH,&elem_hole_std_depth);
	status = ProElemtreeElementAdd (elem_hle_com,NULL,elem_hole_std_depth);
	status = ProElementAlloc (PRO_E_HOLE_DEPTH_TO,&elem_hole_depth_to);
	status = ProElemtreeElementAdd (elem_hole_std_depth,NULL,elem_hole_depth_to);
	status = ProElementAlloc (PRO_E_HOLE_DEPTH_TO_TYPE,&elem_hole_depth_to_type);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_HLE_STRGHT_THRU_ALL_DEPTH;
	status = UserElemtreeElementAdd (elem_hole_depth_to,elem_hole_depth_to_type,value_data);
	status = ProElementAlloc (PRO_E_HOLE_DEPTH_FROM,&elem_hole_depth_from);
	status = ProElemtreeElementAdd (elem_hole_std_depth,NULL,elem_hole_depth_from);
	status = ProElementAlloc (PRO_E_HOLE_DEPTH_FROM_TYPE,&elem_hole_depth_from_type);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_HLE_STRGHT_NONE_DEPTH;


	status = UserElemtreeElementAdd (elem_hole_depth_from,elem_hole_depth_from_type,value_data);
	status = ProElementAlloc (PRO_E_HLE_PLACEMENT,&elem_hle_placement);
	status = ProElemtreeElementAdd (feat_elemtree,NULL,elem_hle_placement);
	status = ProElementAlloc (PRO_E_HLE_PRIM_REF,&elem_hle_prim_ref);
	status = ProSelect ("datum,surface",1,NULL,NULL,NULL,NULL,&p_selection,&n_selection);
	if (n_selection <= 0) return PRO_TK_NO_ERROR;
	value_data.type = PRO_VALUE_TYPE_SELECTION;
	value_data.v.r = p_selection[0];
	status = UserElemtreeElementAdd (elem_hle_placement,elem_hle_prim_ref,value_data);
	status = ProElementAlloc (PRO_E_HLE_PL_TYPE,&elem_hle_pl_type);
	value_data.type = PRO_VALUE_TYPE_INT;
	value_data.v.i = PRO_HLE_PL_TYPE_LIN;
	status = UserElemtreeElementAdd (elem_hle_placement,elem_hle_pl_type,value_data);
	status = ProElementAlloc (PRO_E_HLE_DIM_REF1,&elem_hle_dim_ref1);
	status = ProSelect("datum,surface,edge",1,NULL,NULL,NULL,NULL,&p_selection,&n_selection);
	
	if (n_selection <= 0) return PRO_TK_NO_ERROR;
	value_data.type = PRO_VALUE_TYPE_SELECTION;
	value_data.v.r = p_selection[0];
	status = UserElemtreeElementAdd (elem_hle_placement,elem_hle_dim_ref1,value_data);
	status = ProElementAlloc (PRO_E_HLE_DIM_DIST1,&elem_hle_dim_dist1);
	value_data.type = PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d = -100.0;
	
	status = UserElemtreeElementAdd (elem_hle_placement,elem_hle_dim_dist1,value_data);
	
	status = ProElementAlloc (PRO_E_HLE_DIM_REF2,&elem_hle_dim_ref2);
	status = ProSelect ("datum,surface,edge",1,NULL,NULL,NULL,NULL,&p_selection,&n_selection);
	if (n_selection <= 0) return PRO_TK_NO_ERROR;
	value_data.type = PRO_VALUE_TYPE_SELECTION;
	value_data.v.r = p_selection[0];
	status = UserElemtreeElementAdd (elem_hle_placement,elem_hle_dim_ref2,value_data);
	status = ProElementAlloc (PRO_E_HLE_DIM_DIST2,&elem_hle_dim_dist2);
	value_data.type = PRO_VALUE_TYPE_DOUBLE;
	value_data.v.d = -200.0;
	status = UserElemtreeElementAdd (elem_hle_placement,elem_hle_dim_dist2,value_data);
	status = ProMdlCurrentGet (&model);

	status = ProMdlToModelitem (model,&model_item);
	status = ProSelectionAlloc(NULL,&model_item,&model_selection);
	status = ProFeatureCreate(model_selection,feat_elemtree,options,1,&created_feature,&p_errors);
	status = ProElementFree(&feat_elemtree);
	status = ProSelectionFree(&model_selection);
	return (status);

}
int Menu4(uiCmdCmdId command,uiCmdValue * p_value,void * p_push_command_data)
{	
	//创建孔
	ProDemoHoleCreate();
	return 0;
}
/*
void CDemodlg1::OnBnClickedOk()
{
	CString name = _T("");
	m_name.GetWindowText(name);
	CString value = _T("");
	m_value.GetWindowText(value);
	ProMdl mdl;
	ProMdlCurrentGet(&mdl);
	ProModelitem owner;
	ProMdlToProModelitem(mdl,&owner);
	ProName name2;
	StrCpyW(name2,name,GetBuffer());
	ProParamvalue proval;
	ProParameter param;
	proval.type = PRO_PARAM_STRING;
	StrCpyW(proval.value.s_val,value.GetBuffer());
	ProParameterCreate(&owner,name2,&proval,&param);
	OnOK();
}
*/
int Menu5(uiCmdCmdId command,uiCmdValue * p_value,void * p_push_command_data)
{
	//添加参数
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//CDemodlg dlg;
	//dlg.DoModal();
	return 0;
}
int Menu6(uiCmdCmdId command,uiCmdValue * p_value,void * p_push_command_data)
{
	return 0;
}
extern "C" int user_initialize()
{
	ProError status=ProMenubarMenuAdd(
		"Demo",
		"Demo",
		"Utilities",
		PRO_B_TRUE,
		L"demo.txt");

	uiCmdCmdId cmd_id;
	status=ProCmdActionAdd(
		"DemoMenu1",
		Menu1,
		uiCmdPrioDefault,
		AccessDefault,
		PRO_B_TRUE,
		PRO_B_TRUE,
		&cmd_id);

	status=ProMenubarmenuPushbuttonAdd(
		"Demo",
		"DemoMenu1",
		"DemoMenu1",
		"DemoMenu1ToolTip",
		NULL,
		PRO_B_TRUE,
		cmd_id,
		L"demo.txt");

	status=ProCmdActionAdd(
		"DemoMenu2",
		Menu2,
		uiCmdPrioDefault,
		AccessDefault,
		PRO_B_TRUE,
		PRO_B_TRUE,
		&cmd_id);

	status=ProMenubarmenuPushbuttonAdd(
		"Demo",
		"DemoMenu2",
		"DemoMenu2",
		"DemoMenu2ToolTip",
		NULL,
		PRO_B_TRUE,
		cmd_id,
		L"demo.txt");

	status=ProCmdActionAdd(
		"DemoMenu3",
		Menu3,
		uiCmdPrioDefault,
		AccessDefault,
		PRO_B_TRUE,
		PRO_B_TRUE,
		&cmd_id);

	status=ProMenubarmenuPushbuttonAdd(
		"Demo",
		"DemoMenu3",
		"DemoMenu3",
		"DemoMenu3ToolTip",
		NULL,
		PRO_B_TRUE,
		cmd_id,
		L"demo.txt");

	status=ProCmdActionAdd(
		"DemoMenu4",
		Menu4,
		uiCmdPrioDefault,
		AccessDefault,
		PRO_B_TRUE,
		PRO_B_TRUE,
		&cmd_id);

	status=ProMenubarmenuPushbuttonAdd(
		"Demo",
		"DemoMenu4",
		"DemoMenu4",
		"DemoMenu4ToolTip",
		NULL,
		PRO_B_TRUE,
		cmd_id,
		L"demo.txt");

	status=ProCmdActionAdd(
		"DemoMenu5",
		Menu5,
		uiCmdPrioDefault,
		AccessDefault,
		PRO_B_TRUE,
		PRO_B_TRUE,
		&cmd_id);

	status=ProMenubarmenuPushbuttonAdd(
		"Demo",
		"DemoMenu5",
		"DemoMenu5",
		"DemoMenu5ToolTip",
		NULL,
		PRO_B_TRUE,
		cmd_id,
		L"demo.txt");

	status=ProCmdActionAdd(
		"DemoMenu6",
		Menu6,
		uiCmdPrioDefault,
		AccessDefault,
		PRO_B_TRUE,
		PRO_B_TRUE,
		&cmd_id);

	status=ProMenubarmenuPushbuttonAdd(
		"Demo",
		"DemoMenu6",
		"DemoMenu6",
		"DemoMenu6ToolTip",
		NULL,
		PRO_B_TRUE,
		cmd_id,
		L"demo.txt");

	ProUITranslationFilesEnable();
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}
extern "C" void user_terminate()
{

}