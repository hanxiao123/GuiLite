#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/resource_type.h"
#include "../core_include/bitmap.h"
#include "../core_include/word.h"
#include "../gui_include/font.h"
#include "../gui_include/button.h"
#include "../gui_include/dialog.h"
#include "../core_include/surface.h"
#include "../gui_include/shape_resource.h"

void c_button::pre_create_wnd()
{
	m_style |= GLT_ATTR_VISIBLE | GLT_ATTR_FOCUS | ALIGN_HCENTER | ALIGN_VCENTER;
	m_font_type = FONT_ENG_SMB_AA();
	m_font_color = GLT_RGB(255,255,255);
	m_bg_color = GLT_RGB(36,36,36);
}

void c_button::on_focus(unsigned int w_param)
{
	modify_status(STATUS_FOCUSED);
	on_paint();
}

void c_button::on_kill_focus(void)
{
	modify_status(STATUS_NORMAL);
	on_paint();
}

void c_button::handle_mouse_down_msg(int x, int y)
{
	get_parent()->set_focus(this, 0);
	modify_status(STATUS_PUSHED);
	on_paint();
}

void c_button::handle_mouse_up_msg(int x, int y)
{
	if (STATUS_PUSHED == m_status)
	{
		modify_status(STATUS_FOCUSED);
		on_paint();

		notify_parent(GLT_BN_CLICKED, get_id(), 0);
	}
}

void c_button::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);

	switch(m_status)
	{
	case STATUS_PUSHED:
		if (m_bitmap_pushed)
		{
			draw_bitmap_in_rect(m_bitmap_pushed, rect, m_style);
		}
		else
		{
			draw_custom_shape(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_parent->get_bg_color(), g_shape_btn_push);
		}
		m_font_color = GLT_RGB(255,255,255);

		break;
	case STATUS_FOCUSED:
		if (m_bitmap_focus)
		{
			draw_bitmap_in_rect(m_bitmap_focus, rect, m_style);
		}
		else
		{
			draw_custom_shape(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_parent->get_bg_color(), g_shape_btn_focus);
		}
		m_font_color = GLT_RGB(255,255,255);

		break;
	case STATUS_NORMAL:
		if (m_bitmap)
		{
			draw_bitmap_in_rect(m_bitmap, rect, m_style);
		}
		else
		{
			draw_custom_shape(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_parent->get_bg_color(), g_shape_btn_normal);
		}
		m_font_color = GLT_RGB(255,255,255);

		break;
	case STATUS_DISABLED:
		if (m_bitmap_disable)
		{
			draw_bitmap_in_rect(m_bitmap_disable, rect, m_style);
		}
		else
		{
			draw_custom_shape(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_parent->get_bg_color(), g_shape_btn_disable);
		}
		m_font_color = GLT_RGB(70,73,76);
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	if (m_str_id)
	{
		c_word *p = c_word::get_instance(m_z_order, m_surface);
		p->set_font(m_font_type);
		p->set_color(m_font_color, COLOR_TRANPARENT);
		p->draw_string_in_rect(m_str_id, rect, m_style);
	}
}
