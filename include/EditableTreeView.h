#pragma once

#include <TGUI/TGUI.hpp>

class EditableTreeView : public tgui::TreeView
{
	/* Attributes */
	using Ptr = std::shared_ptr<EditableTreeView>;
	using ConstPtr = std::shared_ptr<const EditableTreeView>;

public:
	/* Constructor */
	EditableTreeView();

	/* Methods */
	static EditableTreeView::Ptr create() 
	{
		return std::make_shared<EditableTreeView>();
	}
};