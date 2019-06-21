// Copyright 2019 The Grimm Team
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

#include "default_peers.h"

namespace grimm
{
    std::vector<std::string> getDefaultPeers()
    {
        std::vector<std::string> result
        {
#ifdef GRIMM_TESTNET
            "us-nodes.testnet.grimmw.com:8100",
            "eu-nodes.testnet.grimmw.com:8100",
            "ap-nodes.testnet.grimmw.com:8100"
#else
            "eu-node01.masternet.grimmw.com:8100",
            "eu-node02.masternet.grimmw.com:8100",
            "eu-node03.masternet.grimmw.com:8100",
            "eu-node04.masternet.grimmw.com:8100"
#endif
        };

        return result;
    }
}