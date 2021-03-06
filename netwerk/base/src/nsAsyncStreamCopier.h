/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2002
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Darin Fisher <darin@netscape.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef nsAsyncStreamCopier_h__
#define nsAsyncStreamCopier_h__

#include "nsIAsyncStreamCopier.h"
#include "nsIAsyncInputStream.h"
#include "nsIAsyncOutputStream.h"
#include "nsIRequestObserver.h"
#include "nsStreamUtils.h"
#include "nsCOMPtr.h"
#include "prlock.h"

//-----------------------------------------------------------------------------

class nsAsyncStreamCopier : public nsIAsyncStreamCopier
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIREQUEST
    NS_DECL_NSIASYNCSTREAMCOPIER

    nsAsyncStreamCopier();
    virtual ~nsAsyncStreamCopier();

    //-------------------------------------------------------------------------
    // these methods may be called on any thread

    PRBool IsComplete(nsresult *status = nsnull);
    void   Complete(nsresult status);

private:

    static void OnAsyncCopyComplete(void *, nsresult);

    nsCOMPtr<nsIInputStream>       mSource;
    nsCOMPtr<nsIOutputStream>      mSink;

    nsCOMPtr<nsIRequestObserver>   mObserver;
    nsCOMPtr<nsISupports>          mObserverContext;

    nsCOMPtr<nsIEventTarget>       mTarget;

    nsCOMPtr<nsISupports>          mCopierCtx;

    PRLock                        *mLock;

    nsAsyncCopyMode                mMode;
    PRUint32                       mChunkSize;
    nsresult                       mStatus;
    PRPackedBool                   mIsPending;
    PRPackedBool                   mCloseSource;
    PRPackedBool                   mCloseSink;
};

#endif // !nsAsyncStreamCopier_h__
