/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#ifndef DBACCESS_UI_DBTREEVIEW_HXX
#include "dbtreeview.hxx"
#endif
#ifndef _SVTREEBOX_HXX
#include <svtools/svtreebx.hxx>
#endif
#ifndef DBAUI_DBTREELISTBOX_HXX
#include "dbtreelistbox.hxx"
#endif
#ifndef DBAUI_DBTREEMODEL_HXX
#include "dbtreemodel.hxx"
#endif
#include "dbaccess_helpid.hrc"

// .........................................................................
namespace dbaui
{
// .........................................................................

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

DBG_NAME(DBTreeView)
//========================================================================
// class DBTreeView
//========================================================================
DBTreeView::DBTreeView(	Window* pParent, const Reference< XMultiServiceFactory >& _rxORB, WinBits nBits) 
					:	Window( pParent, nBits )
					, m_pTreeListBox(NULL)
{
	DBG_CTOR(DBTreeView,NULL);

	m_pTreeListBox = new DBTreeListBox(this, _rxORB ,WB_HASLINES | WB_SORT | WB_HASBUTTONS | WB_HSCROLL |WB_HASBUTTONSATROOT,sal_True);
	m_pTreeListBox->EnableCheckButton(NULL);
	m_pTreeListBox->SetDragDropMode( 0 );
	m_pTreeListBox->EnableInplaceEditing( sal_True );
	m_pTreeListBox->SetHelpId(HID_TLB_TREELISTBOX);
	m_pTreeListBox->Show();
}

// -----------------------------------------------------------------------------
	
DBTreeView::~DBTreeView()
{
	DBG_DTOR(DBTreeView,NULL);
	if (m_pTreeListBox)
	{
		if (m_pTreeListBox->GetModel())
		{
			m_pTreeListBox->GetModel()->RemoveView(m_pTreeListBox);
			m_pTreeListBox->DisconnectFromModel();
		}
		::std::auto_ptr<Window> aTemp(m_pTreeListBox);
		m_pTreeListBox = NULL;
	}
}

// -----------------------------------------------------------------------------
void DBTreeView::SetPreExpandHandler(const Link& _rHdl)
{
	m_pTreeListBox->SetPreExpandHandler(_rHdl);
}

// -----------------------------------------------------------------------------
void	DBTreeView::setCopyHandler(const Link& _rHdl)
{
	m_pTreeListBox->setCopyHandler(_rHdl);
}
// -----------------------------------------------------------------------------
void DBTreeView::Resize()
{
	Window::Resize();
	m_pTreeListBox->SetPosSizePixel(Point(0,0),GetOutputSizePixel());
}
// -------------------------------------------------------------------------
void DBTreeView::setModel(SvLBoxTreeList* _pTreeModel)
{
	if (_pTreeModel)
		_pTreeModel->InsertView(m_pTreeListBox);
	m_pTreeListBox->SetModel(_pTreeModel);
}

// -------------------------------------------------------------------------
void DBTreeView::setSelChangeHdl( const Link& _rHdl )
{
	m_pTreeListBox->SetSelChangeHdl( _rHdl );
}
// -----------------------------------------------------------------------------
void DBTreeView::GetFocus()
{
	Window::GetFocus();
	if ( m_pTreeListBox )//&& !m_pTreeListBox->HasChildPathFocus())
		m_pTreeListBox->GrabFocus();
}


// .........................................................................
}	// namespace dbaui
// .........................................................................


