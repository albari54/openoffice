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



#ifndef DBACCESS_MIGRATIONERROR_HXX
#define DBACCESS_MIGRATIONERROR_HXX

/** === begin UNO includes === **/
#include <com/sun/star/uno/Any.hxx>
/** === end UNO includes === **/

#include <vector>

//........................................................................
namespace dbmm
{
//........................................................................

    enum MigrationErrorType
    {
        ERR_OPENING_SUB_DOCUMENT_FAILED = 1,
        ERR_CLOSING_SUB_DOCUMENT_FAILED,
        ERR_STORAGE_COMMIT_FAILED,
        ERR_STORING_DATABASEDOC_FAILED,
        ERR_COLLECTING_DOCUMENTS_FAILED,
        ERR_UNEXPECTED_LIBSTORAGE_ELEMENT,
        ERR_CREATING_DBDOC_SCRIPT_STORAGE_FAILED,
        ERR_COMMITTING_SCRIPT_STORAGES_FAILED,
        ERR_GENERAL_SCRIPT_MIGRATION_FAILURE,
        ERR_GENERAL_MACRO_MIGRATION_FAILURE,
        ERR_UNKNOWN_SCRIPT_TYPE,
        ERR_UNKNOWN_SCRIPT_LANGUAGE,
        ERR_UNKNOWN_SCRIPT_NAME_FORMAT,
        ERR_SCRIPT_TRANSLATION_FAILURE,
        ERR_INVALID_SCRIPT_DESCRIPTOR_FORMAT,
        ERR_ADJUSTING_DOCUMENT_EVENTS_FAILED,
        ERR_ADJUSTING_DIALOG_EVENTS_FAILED,
        ERR_ADJUSTING_FORMCOMP_EVENTS_FAILED,
        ERR_BIND_SCRIPT_STORAGE_FAILED,
        ERR_REMOVE_SCRIPTS_STORAGE_FAILED,
        ERR_DOCUMENT_BACKUP_FAILED,
        ERR_UNKNOWN_SCRIPT_FOLDER,
        ERR_EXAMINING_SCRIPTS_FOLDER_FAILED,
        ERR_PASSWORD_VERIFICATION_FAILED,
        ERR_NEW_STYLE_REPORT
    };

	//====================================================================
	//= MigrationError
	//====================================================================
    /** encapsulates information about an error which happened during the migration
    */
	struct MigrationError
	{
        const MigrationErrorType            eType;
        ::std::vector< ::rtl::OUString >    aErrorDetails;
        const ::com::sun::star::uno::Any    aCaughtException;

        MigrationError(
                const MigrationErrorType _eType )
            :eType( _eType )
        {
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::com::sun::star::uno::Any& _rCaughtException )
            :eType( _eType )
            ,aCaughtException( _rCaughtException )
        {
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::rtl::OUString& _rDetail )
            :eType( _eType )
        {
            impl_constructDetails( _rDetail );
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::rtl::OUString& _rDetail,
                const ::com::sun::star::uno::Any& _rCaughtException )
            :eType( _eType )
            ,aCaughtException( _rCaughtException )
        {
            impl_constructDetails( _rDetail );
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::rtl::OUString& _rDetail1,
                const ::rtl::OUString& _rDetail2 )
            :eType( _eType )
        {
            impl_constructDetails( _rDetail1, _rDetail2 );
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::rtl::OUString& _rDetail1,
                const ::rtl::OUString& _rDetail2,
                const ::com::sun::star::uno::Any& _rCaughtException )
            :eType( _eType )
            ,aCaughtException( _rCaughtException )
        {
            impl_constructDetails( _rDetail1, _rDetail2 );
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::rtl::OUString& _rDetail1,
                const ::rtl::OUString& _rDetail2,
                const ::rtl::OUString& _rDetail3,
                const ::com::sun::star::uno::Any& _rCaughtException )
            :eType( _eType )
            ,aCaughtException( _rCaughtException )
        {
            impl_constructDetails( _rDetail1, _rDetail2, _rDetail3 );
        }

        MigrationError(
                const MigrationErrorType _eType,
                const ::rtl::OUString& _rDetail1,
                const ::rtl::OUString& _rDetail2,
                const ::rtl::OUString& _rDetail3 )
            :eType( _eType )
        {
            impl_constructDetails( _rDetail1, _rDetail2, _rDetail3 );
        }

    private:
        void    impl_constructDetails(
                    const ::rtl::OUString& _rDetail1,
                    const ::rtl::OUString& _rDetail2 = ::rtl::OUString(),
                    const ::rtl::OUString& _rDetail3 = ::rtl::OUString()
                )
        {
            if ( _rDetail1.getLength() ) aErrorDetails.push_back( _rDetail1 );
            if ( _rDetail2.getLength() ) aErrorDetails.push_back( _rDetail2 );
            if ( _rDetail3.getLength() ) aErrorDetails.push_back( _rDetail3 );
        }
	};

//........................................................................
} // namespace dbmm
//........................................................................

#endif // DBACCESS_MIGRATIONERROR_HXX

