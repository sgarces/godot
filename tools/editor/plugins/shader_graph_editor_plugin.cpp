/*************************************************************************/
/*  shader_graph_editor_plugin.cpp                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#include "shader_graph_editor_plugin.h"


#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "spatial_editor_plugin.h"

////cbacks
///
void ShaderGraphView::_scalar_const_changed(double p_value,int p_id) {

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Scalar Constant",true);
	ur->add_do_method(graph.ptr(),"scalar_const_node_set_value",type,p_id,p_value);
	ur->add_undo_method(graph.ptr(),"scalar_const_node_set_value",type,p_id,graph->scalar_const_node_get_value(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
}

void ShaderGraphView::_vec_const_changed(double p_value, int p_id,Array p_arr){

	Vector3 val;
	for(int i=0;i<p_arr.size();i++) {
		val[i]=p_arr[i].call("get_val");
	}

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Vec Constant",true);
	ur->add_do_method(graph.ptr(),"vec_const_node_set_value",type,p_id,val);
	ur->add_undo_method(graph.ptr(),"vec_const_node_set_value",type,p_id,graph->vec_const_node_get_value(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_rgb_const_changed(const Color& p_color, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change RGB Constant",true);
	ur->add_do_method(graph.ptr(),"rgb_const_node_set_value",type,p_id,p_color);
	ur->add_undo_method(graph.ptr(),"rgb_const_node_set_value",type,p_id,graph->rgb_const_node_get_value(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_scalar_op_changed(int p_op, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Scalar Operator");
	ur->add_do_method(graph.ptr(),"scalar_op_node_set_op",type,p_id,p_op);
	ur->add_undo_method(graph.ptr(),"scalar_op_node_set_op",type,p_id,graph->scalar_op_node_get_op(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_vec_op_changed(int p_op, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Vec Operator");
	ur->add_do_method(graph.ptr(),"vec_op_node_set_op",type,p_id,p_op);
	ur->add_undo_method(graph.ptr(),"vec_op_node_set_op",type,p_id,graph->vec_op_node_get_op(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
}
void ShaderGraphView::_vec_scalar_op_changed(int p_op, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change VecxScalar Operator");
	ur->add_do_method(graph.ptr(),"vec_scalar_op_node_set_op",type,p_id,p_op);
	ur->add_undo_method(graph.ptr(),"vec_scalar_op_node_set_op",type,p_id,graph->vec_scalar_op_node_get_op(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_rgb_op_changed(int p_op, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change RGB Operator");
	ur->add_do_method(graph.ptr(),"rgb_op_node_set_op",type,p_id,p_op);
	ur->add_undo_method(graph.ptr(),"rgb_op_node_set_op",type,p_id,graph->rgb_op_node_get_op(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
}
void ShaderGraphView::_xform_inv_rev_changed(bool p_enabled, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Toggle Rot Only");
	ur->add_do_method(graph.ptr(),"xform_vec_mult_node_set_no_translation",type,p_id,p_enabled);
	ur->add_undo_method(graph.ptr(),"xform_vec_mult_node_set_no_translation",type,p_id,graph->xform_vec_mult_node_get_no_translation(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
}
void ShaderGraphView::_scalar_func_changed(int p_func, int p_id){


	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Scalar Function");
	ur->add_do_method(graph.ptr(),"scalar_func_node_set_function",type,p_id,p_func);
	ur->add_undo_method(graph.ptr(),"scalar_func_node_set_function",type,p_id,graph->scalar_func_node_get_function(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
}
void ShaderGraphView::_vec_func_changed(int p_func, int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Vec Function");
	ur->add_do_method(graph.ptr(),"vec_func_node_set_function",type,p_id,p_func);
	ur->add_undo_method(graph.ptr(),"vec_func_node_set_function",type,p_id,graph->vec_func_node_get_function(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_scalar_input_changed(double p_value,int p_id){

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Scalar Uniform",true);
	ur->add_do_method(graph.ptr(),"scalar_input_node_set_value",type,p_id,p_value);
	ur->add_undo_method(graph.ptr(),"scalar_input_node_set_value",type,p_id,graph->scalar_input_node_get_value(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_vec_input_changed(double p_value, int p_id,Array p_arr){

	Vector3 val;
	for(int i=0;i<p_arr.size();i++) {
		val[i]=p_arr[i].call("get_val");
	}

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Vec Uniform",true);
	ur->add_do_method(graph.ptr(),"vec_input_node_set_value",type,p_id,val);
	ur->add_undo_method(graph.ptr(),"vec_input_node_set_value",type,p_id,graph->vec_input_node_get_value(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}
void ShaderGraphView::_xform_input_changed(int p_id, Node *p_button){

	print_line("XFIC");
	ToolButton *tb = p_button->cast_to<ToolButton>();
	ped_popup->set_pos(tb->get_global_pos()+Vector2(0,tb->get_size().height));
	ped_popup->set_size(tb->get_size());
	edited_id=p_id;
	ped_popup->edit(NULL,"",Variant::TRANSFORM,graph->xform_input_node_get_value(type,p_id),PROPERTY_HINT_NONE,"");
	ped_popup->popup();

}
void ShaderGraphView::_xform_const_changed(int p_id, Node *p_button){

	ToolButton *tb = p_button->cast_to<ToolButton>();
	ped_popup->set_pos(tb->get_global_pos()+Vector2(0,tb->get_size().height));
	ped_popup->set_size(tb->get_size());
	edited_id=p_id;
	ped_popup->edit(NULL,"",Variant::TRANSFORM,graph->xform_const_node_get_value(type,p_id),PROPERTY_HINT_NONE,"");
	ped_popup->popup();

}

void ShaderGraphView::_rgb_input_changed(const Color& p_color, int p_id){


	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change RGB Uniform",true);
	ur->add_do_method(graph.ptr(),"rgb_input_node_set_value",type,p_id,p_color);
	ur->add_undo_method(graph.ptr(),"rgb_input_node_set_value",type,p_id,graph->rgb_input_node_get_value(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
}
void ShaderGraphView::_tex_input_change(int p_id, Node *p_button){


}
void ShaderGraphView::_cube_input_change(int p_id){


}

void ShaderGraphView::_variant_edited() {

	if (graph->node_get_type(type,edited_id)==ShaderGraph::NODE_XFORM_CONST) {

		UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
		ur->create_action("Change XForm Uniform");
		ur->add_do_method(graph.ptr(),"xform_const_node_set_value",type,edited_id,ped_popup->get_variant());
		ur->add_undo_method(graph.ptr(),"xform_const_node_set_value",type,edited_id,graph->xform_const_node_get_value(type,edited_id));
		ur->add_do_method(this,"_update_graph");
		ur->add_undo_method(this,"_update_graph");
		ur->commit_action();
	}


	if (graph->node_get_type(type,edited_id)==ShaderGraph::NODE_XFORM_INPUT) {

		UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
		ur->create_action("Change XForm Uniform");
		ur->add_do_method(graph.ptr(),"xform_input_node_set_value",type,edited_id,ped_popup->get_variant());
		ur->add_undo_method(graph.ptr(),"xform_input_node_set_value",type,edited_id,graph->xform_input_node_get_value(type,edited_id));
		ur->add_do_method(this,"_update_graph");
		ur->add_undo_method(this,"_update_graph");
		ur->commit_action();
	}

	if (graph->node_get_type(type,edited_id)==ShaderGraph::NODE_TEXTURE_INPUT) {

		UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
		ur->create_action("Change Texture Uniform");
		ur->add_do_method(graph.ptr(),"texture_input_node_set_value",type,edited_id,ped_popup->get_variant());
		ur->add_undo_method(graph.ptr(),"texture_input_node_set_value",type,edited_id,graph->texture_input_node_get_value(type,edited_id));
		ur->add_do_method(this,"_update_graph");
		ur->add_undo_method(this,"_update_graph");
		ur->commit_action();
	}

	if (graph->node_get_type(type,edited_id)==ShaderGraph::NODE_CUBEMAP_INPUT) {

		UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
		ur->create_action("Change Cubemap Uniform");
		ur->add_do_method(graph.ptr(),"cubemap_input_node_set_value",type,edited_id,ped_popup->get_variant());
		ur->add_undo_method(graph.ptr(),"cubemap_input_node_set_value",type,edited_id,graph->cubemap_input_node_get_value(type,edited_id));
		ur->add_do_method(this,"_update_graph");
		ur->add_undo_method(this,"_update_graph");
		ur->commit_action();
	}

}

void ShaderGraphView::_comment_edited(int p_id,Node* p_button) {

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	TextEdit *te=p_button->cast_to<TextEdit>();
	ur->create_action("Change Comment",true);
	ur->add_do_method(graph.ptr(),"comment_node_set_text",type,p_id,te->get_text());
	ur->add_undo_method(graph.ptr(),"comment_node_set_text",type,p_id,graph->comment_node_get_text(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;

}


void ShaderGraphView::_input_name_changed(const String& p_name, int p_id, Node *p_line_edit) {

	LineEdit *le=p_line_edit->cast_to<LineEdit>();
	ERR_FAIL_COND(!le);

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Change Input Name");
	ur->add_do_method(graph.ptr(),"input_node_set_name",type,p_id,p_name);
	ur->add_undo_method(graph.ptr(),"input_node_set_name",type,p_id,graph->input_node_get_name(type,p_id));
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	block_update=true;
	ur->commit_action();
	block_update=false;
	le->set_text(graph->input_node_get_name(type,p_id));
}

void ShaderGraphView::_tex_edited(int p_id,Node* p_button) {

	ToolButton *tb = p_button->cast_to<ToolButton>();
	ped_popup->set_pos(tb->get_global_pos()+Vector2(0,tb->get_size().height));
	ped_popup->set_size(tb->get_size());
	edited_id=p_id;
	ped_popup->edit(NULL,"",Variant::OBJECT,graph->texture_input_node_get_value(type,p_id),PROPERTY_HINT_RESOURCE_TYPE,"Texture");
}

void ShaderGraphView::_cube_edited(int p_id,Node* p_button) {

	ToolButton *tb = p_button->cast_to<ToolButton>();
	ped_popup->set_pos(tb->get_global_pos()+Vector2(0,tb->get_size().height));
	ped_popup->set_size(tb->get_size());
	edited_id=p_id;
	ped_popup->edit(NULL,"",Variant::OBJECT,graph->cubemap_input_node_get_value(type,p_id),PROPERTY_HINT_RESOURCE_TYPE,"CubeMap");
}


//////////////view/////////////


void ShaderGraphView::_connection_request(const String& p_from, int p_from_slot,const String& p_to,int p_to_slot) {

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();

	int from_idx=-1;
	int to_idx=-1;
	for (Map<int,GraphNode*>::Element *E=node_map.front();E;E=E->next()) {

		if (p_from==E->get()->get_name())
			from_idx=E->key();
		if (p_to==E->get()->get_name())
			to_idx=E->key();
	}

	ERR_FAIL_COND(from_idx==-1);
	ERR_FAIL_COND(to_idx==-1);

	ur->create_action("Connect Graph Nodes");

	List<ShaderGraph::Connection> conns;

	graph->get_node_connections(type,&conns);
	//disconnect/reconnect dependencies
	ur->add_undo_method(graph.ptr(),"disconnect_node",type,from_idx,p_from_slot,to_idx,p_to_slot);
	for(List<ShaderGraph::Connection>::Element *E=conns.front();E;E=E->next()) {

		if (E->get().dst_id==to_idx && E->get().dst_slot==p_to_slot) {
			ur->add_do_method(graph.ptr(),"disconnect_node",type,E->get().src_id,E->get().src_slot,E->get().dst_id,E->get().dst_slot);
			ur->add_undo_method(graph.ptr(),"connect_node",type,E->get().src_id,E->get().src_slot,E->get().dst_id,E->get().dst_slot);
		}
	}
	ur->add_do_method(graph.ptr(),"connect_node",type,from_idx,p_from_slot,to_idx,p_to_slot);
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	ur->commit_action();


}

void ShaderGraphView::_node_removed(int p_id) {

	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Remove Shader Graph Node");

	ur->add_do_method(graph.ptr(),"node_remove",type,p_id);
	ur->add_undo_method(graph.ptr(),"node_add",type,graph->node_get_type(type,p_id),p_id);
	ur->add_undo_method(graph.ptr(),"node_set_state",type,p_id,graph->node_get_state(type,p_id));
	List<ShaderGraph::Connection> conns;

	graph->get_node_connections(type,&conns);
	for(List<ShaderGraph::Connection>::Element *E=conns.front();E;E=E->next()) {

		if (E->get().dst_id==p_id || E->get().src_id==p_id) {
			ur->add_undo_method(graph.ptr(),"connect_node",type,E->get().src_id,E->get().src_slot,E->get().dst_id,E->get().dst_slot);
		}
	}
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	ur->commit_action();

}

void ShaderGraphView::_node_moved(const Vector2& p_from, const Vector2& p_to,int p_id) {

	print_line("moved from "+p_from+" to "+p_to);
	ERR_FAIL_COND(!node_map.has(p_id));
	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Move Shader Graph Node");
	ur->add_do_method(this,"_move_node",p_id,p_to);
	ur->add_undo_method(this,"_move_node",p_id,p_from);
	ur->commit_action();
}

void ShaderGraphView::_move_node(int p_id,const Vector2& p_to) {

	ERR_FAIL_COND(!node_map.has(p_id));
	node_map[p_id]->set_offset(p_to);
	graph->node_set_pos(type,p_id,p_to);
}


void ShaderGraphView::_create_node(int p_id) {


	GraphNode *gn = memnew( GraphNode );
	gn->set_show_close_button(true);
	Color typecol[4]={
		Color(0.2,1,0.2),
		Color(0.7,0.1,1),
		Color(1,0.2,0.2),
		Color(0,1,1)
	};


	switch(graph->node_get_type(type,p_id)) {

		case ShaderGraph::NODE_INPUT: {

			gn->set_title("Input");

			List<ShaderGraph::SlotInfo> si;
			ShaderGraph::get_input_output_node_slot_info(graph->get_mode(),type,&si);

			int idx=0;
			for (List<ShaderGraph::SlotInfo>::Element *E=si.front();E;E=E->next()) {
				ShaderGraph::SlotInfo& s=E->get();
				if (s.dir==ShaderGraph::SLOT_IN) {

					Label *l= memnew( Label );
					l->set_text(s.name);
					l->set_align(Label::ALIGN_RIGHT);
					gn->add_child(l);
					gn->set_slot(idx,false,0,Color(),true,s.type,typecol[s.type]);
					idx++;
				}
			}

		} break; // all inputs (case Shader type dependent)
		case ShaderGraph::NODE_SCALAR_CONST: {
			gn->set_title("Scalar");
			SpinBox *sb = memnew( SpinBox );
			sb->set_min(-100000);
			sb->set_max(100000);
			sb->set_step(0.001);
			sb->set_val(graph->scalar_const_node_get_value(type,p_id));
			sb->connect("value_changed",this,"_scalar_const_changed",varray(p_id));
			gn->add_child(sb);
			gn->set_slot(0,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; //scalar constant
		case ShaderGraph::NODE_VEC_CONST: {

			gn->set_title("Vector");
			Array v3p(true);
			for(int i=0;i<3;i++) {
				HBoxContainer *hbc = memnew( HBoxContainer );
				Label *l = memnew( Label );
				l->set_text(String::chr('X'+i));
				hbc->add_child(l);
				SpinBox *sb = memnew( SpinBox );
				sb->set_h_size_flags(Control::SIZE_EXPAND_FILL);
				sb->set_min(-100000);
				sb->set_max(100000);
				sb->set_step(0.001);
				sb->set_val(graph->vec_const_node_get_value(type,p_id)[i]);
				sb->connect("value_changed",this,"_vec_const_changed",varray(p_id,v3p));
				v3p.push_back(sb);
				hbc->add_child(sb);
				gn->add_child(hbc);
			}
			gn->set_slot(0,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);

		} break; //vec3 constant
		case ShaderGraph::NODE_RGB_CONST: {

			gn->set_title("Color");
			ColorPickerButton *cpb = memnew( ColorPickerButton );
			cpb->set_color(graph->rgb_const_node_get_value(type,p_id));
			cpb->connect("color_changed",this,"_rgb_const_changed",varray(p_id));
			gn->add_child(cpb);
			Label *l = memnew( Label );
			l->set_text("RGB");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);
			l = memnew( Label );
			l->set_text("Alpha");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);

			gn->set_slot(1,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(2,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; //rgb constant (shows a color picker instead)
		case ShaderGraph::NODE_XFORM_CONST: {
			gn->set_title("XForm");
			ToolButton *edit = memnew( ToolButton );
			edit->set_text("edit..");
			edit->connect("pressed",this,"_xform_const_changed",varray(p_id,edit));
			gn->add_child(edit);
			gn->set_slot(0,false,0,Color(),true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM]);

		} break; // 4x4 matrix constant
		case ShaderGraph::NODE_TIME: {

			gn->set_title("Time");
			Label *l = memnew( Label );
			l->set_text("(s)");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);
			gn->set_slot(0,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; // time in seconds
		case ShaderGraph::NODE_SCREEN_TEX: {

			gn->set_title("ScreenTex");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("UV")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("RGB")));
			gn->add_child(hbc);
			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);

		} break; // screen texture sampler (takes UV) (only usable in fragment case Shader)
		case ShaderGraph::NODE_SCALAR_OP: {

			gn->set_title("ScalarOp");
			static const char* op_name[ShaderGraph::SCALAR_MAX_OP]={
				"Add",
				"Sub",
				"Mul",
				"Div",
				"Mod",
				"Pow",
				"Max",
				"Min",
				"Atan2"
			};

			OptionButton *ob = memnew( OptionButton );
			for(int i=0;i<ShaderGraph::SCALAR_MAX_OP;i++) {

				ob->add_item(op_name[i],i);
			}

			ob->select(graph->scalar_op_node_get_op(type,p_id));
			ob->connect("item_selected",this,"_scalar_op_changed",varray(p_id));
			gn->add_child(ob);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],false,0,Color());


		} break; // scalar vs scalar op (mul: { } break; add: { } break; div: { } break; etc)
		case ShaderGraph::NODE_VEC_OP: {

			gn->set_title("VecOp");
			static const char* op_name[ShaderGraph::VEC_MAX_OP]={
				"Add",
				"Sub",
				"Mul",
				"Div",
				"Mod",
				"Pow",
				"Max",
				"Min",
				"Cross"
			};

			OptionButton *ob = memnew( OptionButton );
			for(int i=0;i<ShaderGraph::VEC_MAX_OP;i++) {

				ob->add_item(op_name[i],i);
			}

			ob->select(graph->vec_op_node_get_op(type,p_id));
			ob->connect("item_selected",this,"_vec_op_changed",varray(p_id));
			gn->add_child(ob);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());


		} break; // vec3 vs vec3 op (mul: { } break;ad: { } break;div: { } break;crossprod: { } break;etc)
		case ShaderGraph::NODE_VEC_SCALAR_OP: {

			gn->set_title("VecScalarOp");
			static const char* op_name[ShaderGraph::VEC_SCALAR_MAX_OP]={
				"Mul",
				"Div",
				"Pow",
			};

			OptionButton *ob = memnew( OptionButton );
			for(int i=0;i<ShaderGraph::VEC_SCALAR_MAX_OP;i++) {

				ob->add_item(op_name[i],i);
			}

			ob->select(graph->vec_scalar_op_node_get_op(type,p_id));
			ob->connect("item_selected",this,"_vec_scalar_op_changed",varray(p_id));
			gn->add_child(ob);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],false,0,Color());


		} break; // vec3 vs scalar op (mul: { } break; add: { } break; div: { } break; etc)
		case ShaderGraph::NODE_RGB_OP: {

			gn->set_title("RGB Op");
			static const char* op_name[ShaderGraph::RGB_MAX_OP]={
				"Screen",
				"Difference",
				"Darken",
				"Lighten",
				"Overlay",
				"Dodge",
				"Burn",
				"SoftLight",
				"HardLight"
			};

			OptionButton *ob = memnew( OptionButton );
			for(int i=0;i<ShaderGraph::RGB_MAX_OP;i++) {

				ob->add_item(op_name[i],i);
			}

			ob->select(graph->rgb_op_node_get_op(type,p_id));
			ob->connect("item_selected",this,"_rgb_op_changed",varray(p_id));
			gn->add_child(ob);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());

		} break; // vec3 vs vec3 rgb op (with scalar amount): { } break; like brighten: { } break; darken: { } break; burn: { } break; dodge: { } break; multiply: { } break; etc.
		case ShaderGraph::NODE_XFORM_MULT: {

			gn->set_title("XFMult");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM],true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM]);
			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM],false,0,Color());


		} break; // mat4 x mat4
		case ShaderGraph::NODE_XFORM_VEC_MULT:
		case ShaderGraph::NODE_XFORM_VEC_INV_MULT: {

			if (graph->node_get_type(type,p_id)==ShaderGraph::NODE_XFORM_VEC_INV_MULT)
				gn->set_title("XFVecMult");
			else
				gn->set_title("XFVecInvMult");


			Button *button = memnew( Button("RotOnly"));
			button->set_toggle_mode(true);
			button->set_pressed(graph->xform_vec_mult_node_get_no_translation(type,p_id));
			button->connect("toggled",this,"_xform_inv_rev_changed",varray(p_id));

			gn->add_child(button);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("xf")));
			hbc->add_spacer();
			Label *l = memnew(Label("out"));
			l->set_align(Label::ALIGN_RIGHT);
			hbc->add_child( l);
			gn->add_child(hbc);
			gn->add_child( memnew(Label("vec")));

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());


		} break; // mat4 x vec3 inverse mult (with no-translation option)
		case ShaderGraph::NODE_SCALAR_FUNC: {

			gn->set_title("ScalarFunc");
			static const char* func_name[ShaderGraph::SCALAR_MAX_FUNC]={
				"Sin",
				"Cos",
				"Tan",
				"ASin",
				"ACos",
				"ATan",
				"SinH",
				"CosH",
				"TanH",
				"Log",
				"Exp",
				"Sqrt",
				"Abs",
				"Sign",
				"Floor",
				"Round",
				"Ceil",
				"Frac",
				"Satr",
				"Neg"
			};

			OptionButton *ob = memnew( OptionButton );
			for(int i=0;i<ShaderGraph::SCALAR_MAX_FUNC;i++) {

				ob->add_item(func_name[i],i);
			}

			ob->select(graph->scalar_func_node_get_function(type,p_id));
			ob->connect("item_selected",this,"_scalar_func_changed",varray(p_id));
			gn->add_child(ob);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_child( memnew(Label("in")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);


		} break; // scalar function (sin: { } break; cos: { } break; etc)
		case ShaderGraph::NODE_VEC_FUNC: {



			gn->set_title("VecFunc");
			static const char* func_name[ShaderGraph::VEC_MAX_FUNC]={
				"Normalize",
				"Saturate",
				"Negate",
				"Reciprocal",
				"RGB to HSV",
				"HSV to RGB",
			};

			OptionButton *ob = memnew( OptionButton );
			for(int i=0;i<ShaderGraph::VEC_MAX_FUNC;i++) {

				ob->add_item(func_name[i],i);
			}

			ob->select(graph->vec_func_node_get_function(type,p_id));
			ob->connect("item_selected",this,"_vec_func_changed",varray(p_id));
			gn->add_child(ob);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("in")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("out")));
			gn->add_child(hbc);

			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);

		} break; // vector function (normalize: { } break; negate: { } break; reciprocal: { } break; rgb2hsv: { } break; hsv2rgb: { } break; etc: { } break; etc)
		case ShaderGraph::NODE_VEC_LEN: {
			gn->set_title("VecLength");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_child( memnew(Label("in")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("len")));
			gn->add_child(hbc);

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; // vec3 length
		case ShaderGraph::NODE_DOT_PROD: {

			gn->set_title("DotProduct");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("dp")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);
			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());

		} break; // vec3 . vec3 (dot product -> scalar output)
		case ShaderGraph::NODE_VEC_TO_SCALAR: {

			gn->set_title("Vec2Scalar");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("vec")));
			hbc->add_spacer();
			Label *l=memnew(Label("x"));
			l->set_align(Label::ALIGN_RIGHT);
			hbc->add_child( l);
			gn->add_child(hbc);
			l=memnew(Label("y"));
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child( l );
			l=memnew(Label("z"));
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child( l);

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);
			gn->set_slot(1,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);
			gn->set_slot(2,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);




		} break; // 1 vec3 input: { } break; 3 scalar outputs
		case ShaderGraph::NODE_SCALAR_TO_VEC: {

			gn->set_title("Scalar2Vec");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_child( memnew(Label("x")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("vec")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("y")));
			gn->add_child( memnew(Label("z")));

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],false,0,Color());
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],false,0,Color());

		} break; // 3 scalar input: { } break; 1 vec3 output
		case ShaderGraph::NODE_VEC_TO_XFORM: {

			gn->set_title("Vec2XForm");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("x")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("xf")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("y")));
			gn->add_child( memnew(Label("z")));
			gn->add_child( memnew(Label("ofs")));

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM]);
			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());
			gn->set_slot(3,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());

		} break; // 3 vec input: { } break; 1 xform output
		case ShaderGraph::NODE_XFORM_TO_VEC: {

			gn->set_title("XForm2Vec");

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("xf")));
			hbc->add_spacer();
			Label *l=memnew(Label("x"));
			l->set_align(Label::ALIGN_RIGHT);
			hbc->add_child( l);
			gn->add_child(hbc);
			l=memnew(Label("y"));
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child( l );
			l=memnew(Label("z"));
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child( l);
			l=memnew(Label("ofs"));
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child( l);

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(1,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(2,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(3,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);

		} break; // 3 vec input: { } break; 1 xform output
		case ShaderGraph::NODE_SCALAR_INTERP: {

			gn->set_title("ScalarInterp");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("interp")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));
			gn->add_child( memnew(Label("c")));

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);
			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],false,0,Color());
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR],false,0,Color());


		} break; // scalar interpolation (with optional curve)
		case ShaderGraph::NODE_VEC_INTERP: {

			gn->set_title("VecInterp");
			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_child( memnew(Label("a")));
			hbc->add_spacer();
			hbc->add_child( memnew(Label("interp")));
			gn->add_child(hbc);
			gn->add_child( memnew(Label("b")));
			gn->add_child( memnew(Label("c")));

			gn->set_slot(0,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(1,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());
			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],false,0,Color());

		} break; // vec3 interpolation  (with optional curve)
		case ShaderGraph::NODE_SCALAR_INPUT: {

			gn->set_title("ScalarUniform");
			LineEdit *le = memnew( LineEdit );
			gn->add_child(le);
			le->set_text(graph->input_node_get_name(type,p_id));
			le->connect("text_entered",this,"_input_name_changed",varray(p_id,le));
			SpinBox *sb = memnew( SpinBox );
			sb->set_min(-100000);
			sb->set_max(100000);
			sb->set_step(0.001);
			sb->set_val(graph->scalar_input_node_get_value(type,p_id));
			sb->connect("value_changed",this,"_scalar_input_changed",varray(p_id));
			gn->add_child(sb);
			gn->set_slot(1,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; // scalar uniform (assignable in material)
		case ShaderGraph::NODE_VEC_INPUT: {

			gn->set_title("VectorUniform");
			LineEdit *le = memnew( LineEdit );
			gn->add_child(le);
			le->set_text(graph->input_node_get_name(type,p_id));
			le->connect("text_entered",this,"_input_name_changed",varray(p_id,le));
			Array v3p(true);
			for(int i=0;i<3;i++) {
				HBoxContainer *hbc = memnew( HBoxContainer );
				Label *l = memnew( Label );
				l->set_text(String::chr('X'+i));
				hbc->add_child(l);
				SpinBox *sb = memnew( SpinBox );
				sb->set_h_size_flags(Control::SIZE_EXPAND_FILL);
				sb->set_min(-100000);
				sb->set_max(100000);
				sb->set_step(0.001);
				sb->set_val(graph->vec_input_node_get_value(type,p_id)[i]);
				sb->connect("value_changed",this,"_vec_input_changed",varray(p_id,v3p));
				v3p.push_back(sb);
				hbc->add_child(sb);
				gn->add_child(hbc);
			}
			gn->set_slot(1,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);

		} break; // vec3 uniform (assignable in material)
		case ShaderGraph::NODE_RGB_INPUT: {

			gn->set_title("ColorUniform");
			LineEdit *le = memnew( LineEdit );
			gn->add_child(le);
			le->set_text(graph->input_node_get_name(type,p_id));
			le->connect("text_entered",this,"_input_name_changed",varray(p_id,le));
			ColorPickerButton *cpb = memnew( ColorPickerButton );
			cpb->set_color(graph->rgb_input_node_get_value(type,p_id));
			cpb->connect("color_changed",this,"_rgb_input_changed",varray(p_id));
			gn->add_child(cpb);
			Label *l = memnew( Label );
			l->set_text("RGB");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);
			l = memnew( Label );
			l->set_text("Alpha");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);

			gn->set_slot(2,false,0,Color(),true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(3,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);


		} break; // color uniform (assignable in material)
		case ShaderGraph::NODE_XFORM_INPUT: {
			gn->set_title("XFUniform");
			LineEdit *le = memnew( LineEdit );
			gn->add_child(le);
			le->set_text(graph->input_node_get_name(type,p_id));
			le->connect("text_entered",this,"_input_name_changed",varray(p_id,le));
			ToolButton *edit = memnew( ToolButton );
			edit->set_text("edit..");
			edit->connect("pressed",this,"_xform_input_changed",varray(p_id,edit));
			gn->add_child(edit);
			gn->set_slot(1,false,0,Color(),true,ShaderGraph::SLOT_TYPE_XFORM,typecol[ShaderGraph::SLOT_TYPE_XFORM]);

		} break; // mat4 uniform (assignable in material)
		case ShaderGraph::NODE_TEXTURE_INPUT: {

			gn->set_title("TexUniform");
			LineEdit *le = memnew( LineEdit );
			gn->add_child(le);
			le->set_text(graph->input_node_get_name(type,p_id));
			le->connect("text_entered",this,"_input_name_changed",varray(p_id,le));
			TextureFrame *tex = memnew( TextureFrame );
			tex->set_expand(true);
			tex->set_custom_minimum_size(Size2(80,80));
			gn->add_child(tex);
			tex->set_texture(graph->texture_input_node_get_value(type,p_id));
			ToolButton *edit = memnew( ToolButton );
			edit->set_text("edit..");
			edit->connect("pressed",this,"_tex_edited",varray(p_id,edit));
			gn->add_child(edit);

			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("UV")));
			hbc->add_spacer();
			Label *l=memnew(Label("RGB"));
			l->set_align(Label::ALIGN_RIGHT);
			hbc->add_child(l);
			gn->add_child(hbc);
			l = memnew( Label );
			l->set_text("Alpha");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);

			gn->set_slot(3,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(4,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; // texture input (assignable in material)
		case ShaderGraph::NODE_CUBEMAP_INPUT: {

			gn->set_title("TexUniform");
			LineEdit *le = memnew( LineEdit );
			gn->add_child(le);
			le->set_text(graph->input_node_get_name(type,p_id));
			le->connect("text_entered",this,"_input_name_changed",varray(p_id,le));

			ToolButton *edit = memnew( ToolButton );
			edit->set_text("edit..");
			edit->connect("pressed",this,"_cube_edited",varray(p_id,edit));
			gn->add_child(edit);


			HBoxContainer *hbc = memnew( HBoxContainer );
			hbc->add_constant_override("separation",0);
			hbc->add_child( memnew(Label("UV")));
			hbc->add_spacer();
			Label *l=memnew(Label("RGB"));
			l->set_align(Label::ALIGN_RIGHT);
			hbc->add_child(l);
			gn->add_child(hbc);
			l = memnew( Label );
			l->set_text("Alpha");
			l->set_align(Label::ALIGN_RIGHT);
			gn->add_child(l);

			gn->set_slot(2,true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC],true,ShaderGraph::SLOT_TYPE_VEC,typecol[ShaderGraph::SLOT_TYPE_VEC]);
			gn->set_slot(3,false,0,Color(),true,ShaderGraph::SLOT_TYPE_SCALAR,typecol[ShaderGraph::SLOT_TYPE_SCALAR]);

		} break; // cubemap input (assignable in material)
		case ShaderGraph::NODE_OUTPUT: {
			gn->set_title("Output");

			List<ShaderGraph::SlotInfo> si;
			ShaderGraph::get_input_output_node_slot_info(graph->get_mode(),type,&si);

			int idx=0;
			for (List<ShaderGraph::SlotInfo>::Element *E=si.front();E;E=E->next()) {
				ShaderGraph::SlotInfo& s=E->get();
				if (s.dir==ShaderGraph::SLOT_OUT) {

					Label *l= memnew( Label );
					l->set_text(s.name);
					l->set_align(Label::ALIGN_LEFT);
					gn->add_child(l);
					gn->set_slot(idx,true,s.type,typecol[s.type],false,0,Color());
					idx++;
				}
			}

		} break; // output (case Shader type dependent)
		case ShaderGraph::NODE_COMMENT: {
			gn->set_title("Comment");
			TextEdit *te = memnew(TextEdit);
			te->set_custom_minimum_size(Size2(100,100));
			gn->add_child(te);
			te->set_text(graph->comment_node_get_text(type,p_id));
			te->connect("text_changed",this,"_comment_edited",varray(p_id,te));

		} break; // comment



	}

	gn->connect("dragged",this,"_node_moved",varray(p_id));
	gn->connect("close_request",this,"_node_removed",varray(p_id),CONNECT_DEFERRED);
	graph_edit->add_child(gn);
	node_map[p_id]=gn;
	gn->set_offset(graph->node_get_pos(type,p_id));
	print_line("NODE "+itos(p_id)+" OFS "+gn->get_offset());

}

void ShaderGraphView::_update_graph() {


	if (block_update)
		return;

	for (Map<int,GraphNode*>::Element *E=node_map.front();E;E=E->next()) {

		memdelete(E->get());
	}

	node_map.clear();

	if (!graph.is_valid())
		return;


	List<int> nl;
	graph->get_node_list(type,&nl);
	print_line("graph nodes: "+itos(nl.size()));
	for(List<int>::Element *E=nl.front();E;E=E->next()) {

		_create_node(E->get());
	}
	graph_edit->clear_connections();

	List<ShaderGraph::Connection> connections;
	graph->get_node_connections(type,&connections);
	for(List<ShaderGraph::Connection>::Element *E=connections.front();E;E=E->next()) {

		ERR_CONTINUE(!node_map.has(E->get().src_id) || !node_map.has(E->get().dst_id));
		graph_edit->connect_node(node_map[E->get().src_id]->get_name(),E->get().src_slot,node_map[E->get().dst_id]->get_name(),E->get().dst_slot);
	}



}

void ShaderGraphView::set_graph(Ref<ShaderGraph> p_graph){

	print_line("GRAPH EDIT: "+itos(p_graph.is_valid()));
	graph=p_graph;
	_update_graph();

}

void ShaderGraphView::_notification(int p_what) {

	if (p_what==NOTIFICATION_ENTER_TREE) {

		ped_popup->connect("variant_changed",this,"_variant_edited");
	}
 }

void ShaderGraphView::add_node(int p_type) {

	List<int> existing;
	graph->get_node_list(type,&existing);
	existing.sort();
	int newid=1;
	for(List<int>::Element *E=existing.front();E;E=E->next()) {
		if (!E->next() || (E->get()+1!=E->next()->get())){
			newid=E->get()+1;
			break;
		}
	}

	Vector2 init_ofs(20,20);
	while(true) {
		bool valid=true;
		for(List<int>::Element *E=existing.front();E;E=E->next()) {
			Vector2 pos = graph->node_get_pos(type,E->get());
			if (init_ofs==pos) {
				init_ofs+=Vector2(20,20);
				valid=false;
				break;

			}
		}

		if (valid)
			break;
	}
	UndoRedo *ur=EditorNode::get_singleton()->get_undo_redo();
	ur->create_action("Add Shader Graph Node");
	ur->add_do_method(graph.ptr(),"node_add",type,p_type,newid);
	ur->add_do_method(graph.ptr(),"node_set_pos",type,newid,init_ofs);
	ur->add_undo_method(graph.ptr(),"node_remove",type,newid);
	ur->add_do_method(this,"_update_graph");
	ur->add_undo_method(this,"_update_graph");
	ur->commit_action();

}

void ShaderGraphView::_bind_methods() {

	ObjectTypeDB::bind_method("_update_graph",&ShaderGraphView::_update_graph);
	ObjectTypeDB::bind_method("_node_moved",&ShaderGraphView::_node_moved);
	ObjectTypeDB::bind_method("_move_node",&ShaderGraphView::_move_node);
	ObjectTypeDB::bind_method("_node_removed",&ShaderGraphView::_node_removed);
	ObjectTypeDB::bind_method("_connection_request",&ShaderGraphView::_connection_request);

	ObjectTypeDB::bind_method("_scalar_const_changed",&ShaderGraphView::_scalar_const_changed);
	ObjectTypeDB::bind_method("_vec_const_changed",&ShaderGraphView::_vec_const_changed);
	ObjectTypeDB::bind_method("_rgb_const_changed",&ShaderGraphView::_rgb_const_changed);
	ObjectTypeDB::bind_method("_xform_const_changed",&ShaderGraphView::_xform_const_changed);
	ObjectTypeDB::bind_method("_scalar_op_changed",&ShaderGraphView::_scalar_op_changed);
	ObjectTypeDB::bind_method("_vec_op_changed",&ShaderGraphView::_vec_op_changed);
	ObjectTypeDB::bind_method("_vec_scalar_op_changed",&ShaderGraphView::_vec_scalar_op_changed);
	ObjectTypeDB::bind_method("_rgb_op_changed",&ShaderGraphView::_rgb_op_changed);
	ObjectTypeDB::bind_method("_xform_inv_rev_changed",&ShaderGraphView::_xform_inv_rev_changed);
	ObjectTypeDB::bind_method("_scalar_func_changed",&ShaderGraphView::_scalar_func_changed);
	ObjectTypeDB::bind_method("_vec_func_changed",&ShaderGraphView::_vec_func_changed);
	ObjectTypeDB::bind_method("_scalar_input_changed",&ShaderGraphView::_scalar_input_changed);
	ObjectTypeDB::bind_method("_vec_input_changed",&ShaderGraphView::_vec_input_changed);
	ObjectTypeDB::bind_method("_xform_input_changed",&ShaderGraphView::_xform_input_changed);
	ObjectTypeDB::bind_method("_rgb_input_changed",&ShaderGraphView::_rgb_input_changed);
	ObjectTypeDB::bind_method("_tex_input_change",&ShaderGraphView::_tex_input_change);
	ObjectTypeDB::bind_method("_cube_input_change",&ShaderGraphView::_cube_input_change);
	ObjectTypeDB::bind_method("_input_name_changed",&ShaderGraphView::_input_name_changed);
	ObjectTypeDB::bind_method("_tex_edited",&ShaderGraphView::_tex_edited);
	ObjectTypeDB::bind_method("_variant_edited",&ShaderGraphView::_variant_edited);
	ObjectTypeDB::bind_method("_cube_edited",&ShaderGraphView::_cube_edited);
	ObjectTypeDB::bind_method("_comment_edited",&ShaderGraphView::_comment_edited);

}

ShaderGraphView::ShaderGraphView(ShaderGraph::ShaderType p_type) {

	type=p_type;
	graph_edit = memnew( GraphEdit );
	block_update=false;
	ped_popup = memnew( CustomPropertyEditor );
	graph_edit->add_child(ped_popup);


}


//////////////edit//////////////
void ShaderGraphEditor::edit(Ref<ShaderGraph> p_shader) {

	for(int i=0;i<ShaderGraph::SHADER_TYPE_MAX;i++) {
		graph_edits[i]->set_graph(p_shader);
	}
}

void ShaderGraphEditor::_add_node(int p_type) {

	ShaderGraph::ShaderType shader_type=ShaderGraph::ShaderType(tabs->get_current_tab());

	graph_edits[shader_type]->add_node(p_type);
}


void ShaderGraphEditor::_notification(int p_what) {
	if (p_what==NOTIFICATION_ENTER_TREE) {
		menu->get_popup()->connect("item_pressed",this,"_add_node");


	}
}

void ShaderGraphEditor::_bind_methods() {

	ObjectTypeDB::bind_method("_add_node",&ShaderGraphEditor::_add_node);

}


const char* ShaderGraphEditor::node_names[ShaderGraph::NODE_TYPE_MAX]={
	"Input", // all inputs (shader type dependent)
	"Scalar Constant", //scalar constant
	"Vector Constant", //vec3 constant
	"RGB Constant", //rgb constant (shows a color picker instead)
	"XForm Constant", // 4x4 matrix constant
	"Time:", // time in seconds
	"Screen Sample", // screen texture sampler (takes uv) (only usable in fragment shader)
	"Scalar Operator", // scalar vs scalar op (mul", add", div", etc)
	"Vector Operator", // vec3 vs vec3 op (mul",ad",div",crossprod",etc)
	"Scalar+Vector Operator", // vec3 vs scalar op (mul", add", div", etc)
	"RGB Operator:", // vec3 vs vec3 rgb op (with scalar amount)", like brighten", darken", burn", dodge", multiply", etc.
	"XForm Multiply", // mat4 x mat4
	"XForm+Vector Multiply", // mat4 x vec3 mult (with no-translation option)
	"XForm+Vector InvMultiply:", // mat4 x vec3 inverse mult (with no-translation option)
	"Scalar Function", // scalar function (sin", cos", etc)
	"Vector Function", // vector function (normalize", negate", reciprocal", rgb2hsv", hsv2rgb", etc", etc)
	"Vector Length", // vec3 length
	"Dot Product:", // vec3 . vec3 (dot product -> scalar output)
	"Vector -> Scalars", // 1 vec3 input", 3 scalar outputs
	"Scalars -> Vector", // 3 scalar input", 1 vec3 output
	"XForm -> Vectors", // 3 vec input", 1 xform output
	"Vectors -> XForm:", // 3 vec input", 1 xform output
	"Scalar Interpolate", // scalar interpolation (with optional curve)
	"Vector Interpolate:", // vec3 interpolation  (with optional curve)
	"Scalar Uniform", // scalar uniform (assignable in material)
	"Vector Uniform", // vec3 uniform (assignable in material)
	"RGB Uniform", // color uniform (assignable in material)
	"XForm Uniform", // mat4 uniform (assignable in material)
	"Texture Uniform", // texture input (assignable in material)
	"CubeMap Uniform:", // cubemap input (assignable in material)
	"Output", // output (shader type dependent)
	"Comment", // comment


};
ShaderGraphEditor::ShaderGraphEditor() {

	HBoxContainer *hbc = memnew( HBoxContainer );
	menu = memnew( MenuButton );
	menu->set_text("Add..");
	hbc->add_child(menu);
	add_child(hbc);
	for(int i=0;i<ShaderGraph::NODE_TYPE_MAX;i++) {

		if (i==ShaderGraph::NODE_OUTPUT)
			continue;
		String v = node_names[i];
		bool addsep=false;
		if (v.ends_with(":")) {
			addsep=true;
			v=v.substr(0,v.length()-1);
		}
		menu->get_popup()->add_item(v,i);
		if (addsep)
			menu->get_popup()->add_separator();
	}

	tabs = memnew(TabContainer);
	tabs->set_v_size_flags(SIZE_EXPAND_FILL);
	add_child(tabs);
	const char* sname[ShaderGraph::SHADER_TYPE_MAX]={
		"Vertex",
		"Fragment",
		"Light"
	};
	for(int i=0;i<ShaderGraph::SHADER_TYPE_MAX;i++) {

		graph_edits[i]= memnew( ShaderGraphView(ShaderGraph::ShaderType(i)) );
		add_child(graph_edits[i]);
		graph_edits[i]->get_graph_edit()->set_name(sname[i]);
		tabs->add_child(graph_edits[i]->get_graph_edit());
		graph_edits[i]->get_graph_edit()->connect("connection_request",graph_edits[i],"_connection_request");
	}

	set_custom_minimum_size(Size2(100,300));
}


void ShaderGraphEditorPlugin::edit(Object *p_object) {

	shader_editor->edit(p_object->cast_to<ShaderGraph>());
}

bool ShaderGraphEditorPlugin::handles(Object *p_object) const {

	return p_object->is_type("ShaderGraph");
}

void ShaderGraphEditorPlugin::make_visible(bool p_visible) {

	if (p_visible) {
		shader_editor->show();
	} else {

		shader_editor->hide();
	}

}

ShaderGraphEditorPlugin::ShaderGraphEditorPlugin(EditorNode *p_node) {

	editor=p_node;
	shader_editor = memnew( ShaderGraphEditor );
	shader_editor->hide();
	SpatialEditor::get_singleton()->get_shader_split()->add_child(shader_editor);


//	editor->get_viewport()->add_child(shader_editor);
//	shader_editor->set_area_as_parent_rect();
//	shader_editor->hide();

}


ShaderGraphEditorPlugin::~ShaderGraphEditorPlugin()
{
}



