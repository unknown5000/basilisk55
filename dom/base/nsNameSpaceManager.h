/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef nsNameSpaceManager_h___
#define nsNameSpaceManager_h___

#include "nsDataHashtable.h"
#include "nsHashKeys.h"
#include "nsIAtom.h"
#include "nsIObserver.h"
#include "nsTArray.h"

#include "mozilla/StaticPtr.h"

class nsAString;
class nsIDocument;

/**
 * The Name Space Manager tracks the association between a NameSpace
 * URI and the int32_t runtime id. Mappings between NameSpaces and 
 * NameSpace prefixes are managed by nsINameSpaces.
 *
 * All NameSpace URIs are stored in a global table so that IDs are
 * consistent accross the app. NameSpace IDs are only consistent at runtime
 * ie: they are not guaranteed to be consistent accross app sessions.
 *
 * The nsNameSpaceManager needs to have a live reference for as long as
 * the NameSpace IDs are needed.
 *
 */

class nsNameSpaceManager final : public nsIObserver
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  virtual nsresult RegisterNameSpace(const nsAString& aURI,
                                     int32_t& aNameSpaceID);

  virtual nsresult GetNameSpaceURI(int32_t aNameSpaceID, nsAString& aURI);

  int32_t GetNameSpaceID(const nsAString& aURI,
                         bool aInChromeDoc);
  int32_t GetNameSpaceID(nsIAtom* aURI,
                         bool aInChromeDoc);

  bool HasElementCreator(int32_t aNameSpaceID);

  static nsNameSpaceManager* GetInstance();
  bool mMathMLDisabled;
  bool mSVGDisabled;

private:
  bool Init();
  nsresult AddNameSpace(already_AddRefed<nsIAtom> aURI, const int32_t aNameSpaceID);
  nsresult AddDisabledNameSpace(already_AddRefed<nsIAtom> aURI, const int32_t aNameSpaceID);
  ~nsNameSpaceManager() {};

  nsDataHashtable<nsISupportsHashKey, int32_t> mURIToIDTable;
  nsDataHashtable<nsISupportsHashKey, int32_t> mDisabledURIToIDTable;
  nsTArray<nsCOMPtr<nsIAtom>> mURIArray;

  static mozilla::StaticRefPtr<nsNameSpaceManager> sInstance;
};
 
#endif // nsNameSpaceManager_h___
