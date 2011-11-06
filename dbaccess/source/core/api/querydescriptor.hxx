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



#ifndef _DBA_COREAPI_QUERYDESCRIPTOR_HXX_
#define _DBA_COREAPI_QUERYDESCRIPTOR_HXX_

#ifndef _CPPUHELPER_IMPLBASE3_HXX_
#include <cppuhelper/implbase3.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif

#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _DBA_COREAPI_COLUMN_HXX_
#include "column.hxx"
#endif
#ifndef _DBA_CORE_DATASETTINGS_HXX_
#include "datasettings.hxx"
#endif
#ifndef _DBA_CORE_COMMANDBASE_HXX_
#include "commandbase.hxx"
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif

//........................................................................
namespace dbaccess
{
//........................................................................

//==========================================================================
//= OQueryDescriptor_Base - a query descriptor (as the name suggests :)
//==========================================================================
typedef ::cppu::ImplHelper3<
		::com::sun::star::sdbcx::XColumnsSupplier,
		::com::sun::star::lang::XUnoTunnel,
		::com::sun::star::lang::XServiceInfo >	OQueryDescriptor_BASE;

class OQueryDescriptor_Base
		:public OQueryDescriptor_BASE
		,public OCommandBase
		,public IColumnFactory
		,public ::connectivity::sdbcx::IRefreshableColumns
{
private:
	sal_Bool		m_bColumnsOutOfDate : 1;	// the columns have to be rebuild on the next getColumns ?
	::osl::Mutex&	m_rMutex;

protected:
	OColumns*		m_pColumns;					// our column descriptions
	::rtl::OUString m_sElementName;
	virtual ~OQueryDescriptor_Base();

	void		setColumnsOutOfDate( sal_Bool _bOutOfDate = sal_True );
	sal_Bool	isColumnsOutOfDate() const { return m_bColumnsOutOfDate; }

	sal_Int32	getColumnCount() const { return m_pColumns ? m_pColumns->getCount() : 0; }
	void		clearColumns( );

	void		implAppendColumn( const ::rtl::OUString& _rName, OColumn* _pColumn );

public:
	OQueryDescriptor_Base(::osl::Mutex&	_rMutex,::cppu::OWeakObject& _rMySelf);
	/** constructs the object with a UNO QueryDescriptor. If you use this ctor, the resulting object
		won't have any column informations (the column container will be empty)
	*/
	OQueryDescriptor_Base(const OQueryDescriptor_Base& _rSource,::cppu::OWeakObject& _rMySelf);

// ::com::sun::star::sdbcx::XColumnsSupplier
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getColumns(  ) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::lang::XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);
	DECLARE_IMPLEMENTATION_ID( );

// ::com::sun::star::lang::XServiceInfo
	virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

protected:

// IColumnFactory
	virtual OColumn*	createColumn(const ::rtl::OUString& _rName) const;
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > createColumnDescriptor();
    virtual void columnAppended( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxSourceDescriptor );
	virtual void columnDropped(const ::rtl::OUString& _sName);

	/** rebuild our columns set

        clearColumns has already been called before, do <em>NOT</em> call it, again
    */
	virtual void rebuildColumns( );

	virtual void disposeColumns();

    // IRefreshableColumns overridables
	virtual void refreshColumns();
};

class OQueryDescriptor : public comphelper::OMutexAndBroadcastHelper
						,public ::cppu::OWeakObject
						,public OQueryDescriptor_Base
						,public ::comphelper::OPropertyArrayUsageHelper< OQueryDescriptor_Base >
						,public ODataSettings
{
    OQueryDescriptor(const OQueryDescriptor&);
    void operator =(const OQueryDescriptor&);
	// helper
	void registerProperties();
protected:
	// OPropertyArrayUsageHelper
	virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

	// OPropertySetHelper
	virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    virtual ~OQueryDescriptor();
public:
	OQueryDescriptor();
	OQueryDescriptor(const OQueryDescriptor_Base& _rSource);

	// com::sun::star::lang::XTypeProvider
	DECLARE_TYPEPROVIDER( );

// ::com::sun::star::uno::XInterface
	DECLARE_XINTERFACE( )

	// ::com::sun::star::beans::XPropertySet
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);

};
//........................................................................
}	// namespace dbaccess
//........................................................................

#endif // _DBA_COREAPI_QUERYDESCRIPTOR_HXX_


