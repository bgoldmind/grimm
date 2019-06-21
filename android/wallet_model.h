// Copyright 2018 The Grimm Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "wallet/wallet_client.h"

class WalletModel
    : public grimm::wallet::WalletClient
{
public:

    using Ptr = std::shared_ptr<WalletModel>;

    WalletModel(grimm::wallet::IWalletDB::Ptr walletDB, const std::string& nodeAddr, grimm::io::Reactor::Ptr reactor);
    ~WalletModel() override;

private:
    void onStatus(const grimm::wallet::WalletStatus& status) override;
    void onTxStatus(grimm::wallet::ChangeAction, const std::vector<grimm::wallet::TxDescription>& items) override;
    void onSyncProgressUpdated(int done, int total) override;
    void onChangeCalculated(grimm::Amount change) override;
    void onAllUtxoChanged(const std::vector<grimm::wallet::Coin>& utxos) override;
    void onAddresses(bool own, const std::vector<grimm::wallet::WalletAddress>& addrs) override;
    void onGeneratedNewAddress(const grimm::wallet::WalletAddress& walletAddr) override;
    void onNewAddressFailed() override;
    void onChangeCurrentWalletIDs(grimm::wallet::WalletID senderID, grimm::wallet::WalletID receiverID) override;
    void onNodeConnectionChanged(bool isNodeConnected) override;
    void onWalletError(grimm::wallet::ErrorType error) override;
    void FailedToStartWallet() override;
    void onSendMoneyVerified() override;
    void onCantSendToExpired() override;
    void onPaymentProofExported(const grimm::wallet::TxID& txID, const grimm::ByteBuffer& proof) override;
    void onCoinsByTx(const std::vector<grimm::wallet::Coin>& coins) override;
    void onAddressChecked(const std::string& addr, bool isValid) override;
};