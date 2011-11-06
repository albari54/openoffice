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



#ifndef DBACCESS_DOCUMENTEVENTS_HXX
#define DBACCESS_DOCUMENTEVENTS_HXX

/** === begin UNO includes === **/
#include <com/sun/star/container/XNameReplace.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
/** === end UNO includes === **/

#include <cppuhelper/implbase1.hxx>

#include <memory>
#include <map>
#include <boost/noncopyable.hpp>

//........................................................................
namespace dbaccess
{
//........................................................................

    typedef ::std::map< ::rtl::OUString, ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > >
            DocumentEventsData;

	//====================================================================
	//= DocumentEvents
	//====================================================================
    struct DocumentEvents_Data;

    typedef ::cppu::WeakImplHelper1 <   ::com::sun::star::container::XNameReplace
                                    >   DocumentEvents_Base;

    class DocumentEvents    :public DocumentEvents_Base
                            ,public ::boost::noncopyable
	{
    public:
        DocumentEvents( ::cppu::OWeakObject& _rParent, ::osl::Mutex& _rMutex, DocumentEventsData& _rEventsData );
        ~DocumentEvents();

        static bool needsSynchronousNotification( const ::rtl::OUString& _rEventName );

        // XInterface
	    virtual void SAL_CALL acquire() throw();
	    virtual void SAL_CALL release() throw();

        // XNameReplace
        virtual void SAL_CALL replaceByName( const ::rtl::OUString& aName, const ::com::sun::star::uno::Any& aElement ) throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

        // XNameAccess
        virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw (::com::sun::star::uno::RuntimeException);

        // XElementAccess
        virtual ::com::sun::star::uno::Type SAL_CALL getElementType(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL hasElements(  ) throw (::com::sun::star::uno::RuntimeException);

    private:
        ::std::auto_ptr< DocumentEvents_Data >  m_pData;
	};

//........................................................................
} // namespace dbaccess
//........................................................................

#endif // DBACCESS_DOCUMENTEVENTS_HXX
