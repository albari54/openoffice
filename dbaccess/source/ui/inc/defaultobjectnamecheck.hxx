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



#ifndef DBACCESS_SOURCE_UI_INC_DEFAULTOBJECTNAMECHECK_HXX
#define DBACCESS_SOURCE_UI_INC_DEFAULTOBJECTNAMECHECK_HXX

#ifndef DBACCESS_SOURCE_UI_INC_OBJECTNAMECHECK_HXX
#include "objectnamecheck.hxx"
#endif

/** === begin UNO includes === **/
#ifndef _COM_SUN_STAR_CONTAINER_XHIERARCHICALNAMEACCESS_HPP_
#include <com/sun/star/container/XHierarchicalNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
/** === end UNO includes === **/

#include <memory>
#include <boost/noncopyable.hpp>

//........................................................................
namespace dbaui
{
//........................................................................

    //====================================================================
    //= HierarchicalNameCheck
    //====================================================================
    struct HierarchicalNameCheck_Impl;
    /** class implementing the IObjectNameCheck interface, and checking given object names
        against a hierarchical name container
    */
    class HierarchicalNameCheck :public ::boost::noncopyable
                                ,public IObjectNameCheck
    {
    private:
        std::auto_ptr< HierarchicalNameCheck_Impl > m_pImpl;

    public:
        /** constructs a HierarchicalNameCheck instance
        @param _rxNames
            the hierarchic container of named objects, against which given names should be
            checked
        @param _rRelativeRoot
            the root in the hierarchy against which given names should be checked
        @throws ::com::sun::star::lang::IllegalArgumentException
            if the given container is <NULL/>
        */
        HierarchicalNameCheck(
            const ::com::sun::star::uno::Reference< ::com::sun::star::container::XHierarchicalNameAccess >& _rxNames,
            const ::rtl::OUString& _rRelativeRoot
        );

        ~HierarchicalNameCheck();

        // IObjectNameCheck overridables
        virtual bool    isNameValid(
            const ::rtl::OUString& _rObjectName,
            ::dbtools::SQLExceptionInfo& _out_rErrorToDisplay
        ) const;

    private:
        HierarchicalNameCheck();                                            // never implemented
    };

    //====================================================================
    //= DynamicTableOrQueryNameCheck
    //====================================================================
    struct DynamicTableOrQueryNameCheck_Impl;
    /** class implementing the IObjectNameCheck interface, and checking a given name
        for being valid as either a query or a table name.

        The class can be parametrized to act as either table name or query name validator.

        For databases which support queries in queries, the name check is implicitly extended
        to both queries and tables, no matter which category is checked. This prevents, for
        such databases, that users can create a query with the name of an existing table,
        or vice versa.

        @seealso dbtools::DatabaseMetaData::supportsSubqueriesInFrom
        @seealso com::sun::star::sdb::tools::XObjectNames::checkNameForCreate
    */
    class DynamicTableOrQueryNameCheck  :public ::boost::noncopyable
                                        ,public IObjectNameCheck
    {
    private:
        std::auto_ptr< DynamicTableOrQueryNameCheck_Impl > m_pImpl;

    public:
        /** constructs a DynamicTableOrQueryNameCheck instance
        @param _rxSdbLevelConnection
            a connection supporting the css.sdb.Connection service, in other word, it
            does expose the XTablesSupplier and XQueriesSupplier interfaces.
        @param _nCommandType
            specifies whether table names or query names should be checked. Only valid values
            are CommandType::TABLE and CommandType::QUERY.
        @throws ::com::sun::star::lang::IllegalArgumentException
            if the given connection is <NULL/>, or the given command type is neither
            CommandType::TABLE nor CommandType::QUERY.
        */
        DynamicTableOrQueryNameCheck(
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxSdbLevelConnection,
            sal_Int32 _nCommandType
        );

        ~DynamicTableOrQueryNameCheck();

        // IObjectNameCheck overridables
        virtual bool    isNameValid(
            const ::rtl::OUString& _rObjectName,
            ::dbtools::SQLExceptionInfo& _out_rErrorToDisplay
        ) const;

    private:
        DynamicTableOrQueryNameCheck();                                                // never implemented
    };

//........................................................................
} // namespace dbaui
//........................................................................

#endif // DBACCESS_SOURCE_UI_INC_DEFAULTOBJECTNAMECHECK_HXX

