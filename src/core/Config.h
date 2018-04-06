/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2016-2018 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__


#include <stdint.h>
#include <vector>


#include "core/CommonConfig.h"
#include "rapidjson/fwd.h"
#include "xmrig.h"


class Addr;
class Url;


namespace xmrig {


class ConfigLoader;
class IThread;
class IWatcherListener;


/**
 * @brief The Config class
 *
 * Options with dynamic reload:
 *   colors
 *   debug
 *   verbose
 *   custom-diff (only for new connections)
 *   api/worker-id
 *   pools/
 */
class Config : public CommonConfig
{
public:
    Config();
    ~Config();

    bool reload(const char *json);

    void getJSON(rapidjson::Document &doc) const override;

    inline AlgoVariant algoVariant() const               { return m_algoVariant; }
    inline bool isDoubleHash() const                     { return m_doubleHash; }
    inline bool isDryRun() const                         { return m_dryRun; }
    inline bool isHugePages() const                      { return m_hugePages; }
    inline const std::vector<IThread *> &threads() const { return m_threads; }
    inline int printTime() const                         { return m_printTime; }
    inline int priority() const                          { return m_priority; }
    inline int threadsCount() const                      { return m_threadsCount; }
    inline int64_t affinity() const                      { return m_affinity; }

    static Config *load(int argc, char **argv, IWatcherListener *listener);

protected:
    bool adjust() override;
    bool parseBoolean(int key, bool enable) override;
    bool parseString(int key, const char *arg) override;
    bool parseUint64(int key, uint64_t arg) override;
    void parseJSON(const rapidjson::Document &doc) override;

private:
    bool parseInt(int key, int arg);

    AlgoVariant getAlgoVariant() const;
#   ifndef XMRIG_NO_AEON
    AlgoVariant getAlgoVariantLite() const;
#   endif

    AlgoVariant m_algoVariant;
    bool m_doubleHash;
    bool m_dryRun;
    bool m_hugePages;
    bool m_safe;
    int m_maxCpuUsage;
    int m_printTime;
    int m_priority;
    int64_t m_affinity;
    size_t m_threadsCount;
    std::vector<IThread *> m_threads;
};


} /* namespace xmrig */

#endif /* __CONFIG_H__ */