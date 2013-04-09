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



package mod._cached;

import com.sun.star.beans.Property;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.sdbc.XResultSet;
import com.sun.star.ucb.Command;
import com.sun.star.ucb.NumberedSortingInfo;
import com.sun.star.ucb.OpenCommandArgument2;
import com.sun.star.ucb.OpenMode;
import com.sun.star.ucb.XCachedContentResultSetStubFactory;
import com.sun.star.ucb.XCommandProcessor;
import com.sun.star.ucb.XContent;
import com.sun.star.ucb.XContentIdentifier;
import com.sun.star.ucb.XContentIdentifierFactory;
import com.sun.star.ucb.XContentProvider;
import com.sun.star.ucb.XDynamicResultSet;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XInterface;
import com.sun.star.uno.Type;
import com.sun.star.uno.AnyConverter;
import java.io.PrintWriter;
import lib.StatusException;
import lib.TestCase;
import lib.TestEnvironment;
import lib.TestParameters;

/**
* Test for object which is represented by service
* <code>com.sun.star.ucb.CachedContentResultSetFactory</code>. <p>
* Object implements the following interfaces :
* <ul>
*  <li> <code>com::sun::star::ucb::XCachedContentResultSetFactory</code></li>
* </ul> <p>
* This object test <b> is NOT </b> designed to be run in several
* threads concurently.
* @see com.sun.star.ucb.XCachedContentResultSetFactory
* @see com.sun.star.ucb.CachedContentResultSetFactory
* @see ifc.ucb._XCachedContentResultSetFactory
*/
public class CachedContentResultSetFactory extends TestCase {

    /**
    * Creating a Testenvironment for the interfaces to be tested.
    * Creates an instance of the service
    * <code>com.sun.star.ucb.CachedContentResultSetFactory</code>. <p>
    *     Object relations created :
    * <ul>
    *  <li> <code>'CachedContentResultSetStub'</code> for
    *      {@link ifc.XCachedContentResultSetFactory} : the destination
    *   interface requires as its parameter an instance of
    *   <code>CachedContentResultSetStub</code> service. It is created
    *   using <code>UniversalContentBroker</code> and querying it for
    *   <code>PackageContent</code> which represents JAR file mentioned
    *   above. Then the dynamic list of file contents (entries) is retrieved,
    *   and a static list is created from it. Using
    *   <code>CachedContentResultSetStubFactory</code> service a stub of
    *   Cached result set is created which is relation required.
    *  </li>
    * </ul>
    */
    public TestEnvironment createTestEnvironment( TestParameters Param,
                                                  PrintWriter log )
                                                    throws StatusException {
        XInterface oObj = null;
        Object oInterface = null;
        XMultiServiceFactory xMSF = (XMultiServiceFactory)Param.getMSF();
        Object relationContainer = null ;


        try {
            oInterface = xMSF.createInstance
                ( "com.sun.star.ucb.CachedContentResultSetFactory" );

            // adding one child container
        }
        catch( com.sun.star.uno.Exception e ) {
            log.println("Can't create an object." );
            throw new StatusException( "Can't create an object", e );
        }

        oObj = (XInterface) oInterface;

        TestEnvironment tEnv = new TestEnvironment( oObj );

        // creating relation for XCachedContentResultSetFactory
        XResultSet resSetStub = null ;
        try {
            Object oUCB = xMSF.createInstanceWithArguments
                ("com.sun.star.ucb.UniversalContentBroker",
                new Object[] {"Local", "Office"}) ;

            XContentIdentifierFactory ciFac = (XContentIdentifierFactory)
                UnoRuntime.queryInterface(XContentIdentifierFactory.class, oUCB) ;

            String url = util.utils.getFullTestURL("SwXTextEmbeddedObject.sxw") ;
            String escUrl = "" ;

            // In base URL of a JAR file in content URL all directory
            // separators ('/') must be replaced with escape symbol '%2F'.
            int idx = url.indexOf("/") ;
            int lastIdx = -1 ;
            while (idx >= 0) {
                escUrl += url.substring(lastIdx + 1, idx) + "%2F" ;
                lastIdx = idx ;
                idx = url.indexOf("/", idx + 1) ;
            }
            escUrl += url.substring(lastIdx + 1) ;
            String cntUrl = "vnd.sun.star.pkg://" + escUrl + "/" ;

            XContentIdentifier CI = ciFac.createContentIdentifier(cntUrl) ;

            XContentProvider cntProv = (XContentProvider)
                UnoRuntime.queryInterface(XContentProvider.class, oUCB) ;

            XContent cnt = cntProv.queryContent(CI) ;

            XCommandProcessor cmdProc = (XCommandProcessor)
                UnoRuntime.queryInterface(XCommandProcessor.class, cnt) ;

            Property prop = new Property() ;
            prop.Name = "Title" ;

            Command cmd = new Command("open", -1, new OpenCommandArgument2
                (OpenMode.ALL, 10000, null, new Property[] {prop},
                 new NumberedSortingInfo[0])) ;

            XDynamicResultSet dynResSet = null;
            try {
                dynResSet = (XDynamicResultSet)
                    AnyConverter.toObject(new Type(XDynamicResultSet.class),
                                        cmdProc.execute(cmd, 0, null));
            } catch (com.sun.star.lang.IllegalArgumentException iae) {
                throw new StatusException("Couldn't convert Any ",iae);
            }

            XResultSet resSet = dynResSet.getStaticResultSet() ;

            Object oStubFactory = xMSF.createInstance
                ("com.sun.star.ucb.CachedContentResultSetStubFactory") ;

            XCachedContentResultSetStubFactory xStubFactory =
                (XCachedContentResultSetStubFactory) UnoRuntime.queryInterface
                (XCachedContentResultSetStubFactory.class, oStubFactory) ;

            resSetStub = xStubFactory.createCachedContentResultSetStub(resSet) ;

        } catch (com.sun.star.uno.Exception e) {
            log.println("Can't create relation." );
            e.printStackTrace(log) ;
            throw new StatusException( "Can't create relation", e );
        }

        tEnv.addObjRelation("CachedContentResultSetStub", resSetStub) ;

        return tEnv;
    } // finish method getTestEnvironment

}

