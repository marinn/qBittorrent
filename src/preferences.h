/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QSettings>
#include <QPair>

class Preferences {
public:
  // General options
  static QString getLocale() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/Locale"), "en_GB").toString();
  }

  static int getStyle() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/Style"), 0).toInt();
  }

  static bool confirmOnExit() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/ExitConfirm"), true).toBool();
  }

  static bool speedInTitleBar() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/SpeedInTitleBar"), false).toBool();
  }

  static unsigned int getRefreshInterval() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/RefreshInterval"), 1500).toUInt();
  }

  static bool systrayIntegration() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/SystrayEnabled"), true).toBool();
  }

  static bool isToolbarDisplayed() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/ToolbarDisplayed"), true).toBool();
  }

  static bool minimizeToTray() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/MinimizeToTray"), false).toBool();
  }

  static bool closeToTray() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/CloseToTray"), false).toBool();
  }

  static bool startMinimized() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/StartMinimized"), false).toBool();
  }

  static bool isSlashScreenDisabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/NoSplashScreen"), false).toBool();
  }

  static bool OSDEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/General/NotificationBaloons"), true).toBool();
  }

  // Downloads
  static QString getSavePath() {
    QSettings settings("qBittorrent", "qBittorrent");
#ifdef Q_WS_WIN
    QString home = QDir::rootPath();
#else
    QString home = QDir::homePath();
#endif
    if(home[home.length()-1] != QDir::separator()){
      home += QDir::separator();
    }
    return settings.value(QString::fromUtf8("Preferences/Downloads/SavePath"), home+"qBT_dir").toString();
  }

  static bool isTempPathEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/TempPathEnabled"), false).toBool();
  }

  static QString getTempPath() {
    QSettings settings("qBittorrent", "qBittorrent");
#ifdef Q_WS_WIN
    QString home = QDir::rootPath();
#else
    QString home = QDir::homePath();
#endif
    return settings.value(QString::fromUtf8("Preferences/Downloads/TempPath"), home+"qBT_dir"+QDir::separator()+"temp").toString();
  }

  static bool preAllocateAllFiles() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/PreAllocation"), false).toBool();
  }

  static bool useAdditionDialog() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/AdditionDialog"), true).toBool();
  }

  static bool addTorrentsInPause() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/StartInPause"), false).toBool();
  }

  static bool isDirScanEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/ScanDir"), QString()).toString().isEmpty();
  }

  static QString getScanDir() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/ScanDir"), QString()).toString();
  }

  static int getActionOnDblClOnTorrentDl() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/DblClOnTorDl"), 0).toInt();
  }

  static int getActionOnDblClOnTorrentFn() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Downloads/DblClOnTorFn"), 1).toInt();
  }

  // Connection options
  static int getSessionPort() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/PortRangeMin"), 6881).toInt();
  }

  static bool isUPnPEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/UPnP"), true).toBool();
  }

  static bool isNATPMPEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/NAT-PMP"), true).toBool();
  }

  static int getGlobalDownloadLimit() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/GlobalDLLimit"), -1).toInt();
  }

  static int getGlobalUploadLimit() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/GlobalUPLimit"), -1).toInt();
  }

  // Proxy options
  static bool isHTTPProxyEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxyType"), 0).toInt() > 0;
  }

  static bool isHTTPProxyAuthEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxy/Authentication"), false).toBool();
  }

  static QString getHTTPProxyIp() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxy/IP"), "0.0.0.0").toString();
  }

  static unsigned short getHTTPProxyPort() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxy/Port"), 8080).toInt();
  }

  static QString getHTTPProxyUsername() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxy/Username"), QString()).toString();
  }

  static QString getHTTPProxyPassword() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxy/Password"), QString()).toString();
  }

  static int getHTTPProxyType() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/HTTPProxyType"), 0).toInt();
  }

  static bool isProxyEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/ProxyType"), 0).toInt() > 0;
  }

  static bool isProxyAuthEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/Authentication"), false).toBool();
  }

  static QString getProxyIp() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/IP"), "0.0.0.0").toString();
  }

  static unsigned short getProxyPort() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/Port"), 8080).toInt();
  }

  static QString getProxyUsername() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/Username"), QString()).toString();
  }

  static QString getProxyPassword() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/Password"), QString()).toString();
  }

  static int getProxyType() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/ProxyType"), 0).toInt();
  }

  static bool useProxyForTrackers() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/AffectTrackers"), true).toBool();
  }

  static bool useProxyForPeers() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/AffectPeers"), true).toBool();
  }

  static bool useProxyForWebseeds() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/AffectWebSeeds"), true).toBool();
  }

  static bool useProxyForDHT() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Connection/Proxy/AffectDHT"), true).toBool();
  }

  // Bittorrent options
  static int getMaxConnecs() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/MaxConnecs"), 500).toInt();
  }

  static int getMaxConnecsPerTorrent() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/MaxConnecsPerTorrent"), 100).toInt();
  }

  static int getMaxUploadsPerTorrent() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/MaxUploadsPerTorrent"), 4).toInt();
  }

  static bool isDHTEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/DHT"), true).toBool();
  }

  static bool isDHTPortSameAsBT() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/sameDHTPortAsBT"), true).toBool();
  }

  static int getDHTPort() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/DHTPort"), 6882).toInt();
  }

  static bool isLSDEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/LSD"), true).toBool();
  }

  static bool isUtorrentSpoofingEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/utorrentSpoof"), false).toBool();
  }

  static int getEncryptionSetting() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/Encryption"), 0).toInt();
  }

  static float getDesiredRatio() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/DesiredRatio"), -1).toDouble();
  }

  static float getDeleteRatio() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Bittorrent/MaxRatio"), -1).toDouble();
  }

  // IP Filter
  static bool isFilteringEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/IPFilter/Enabled"), false).toBool();
  }

  static QString getFilter() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/IPFilter/File"), QString()).toString();
  }

  // RSS
  static bool isRSSEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/RSS/RSSEnabled"), false).toBool();
  }

  static int getRSSRefreshInterval() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/RSS/RSSRefresh"), 5).toInt();
  }

  static int getRSSMaxArticlesPerFeed() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/RSS/RSSMaxArticlesPerFeed"), 50).toInt();
  }

  // Queueing system
  static bool isQueueingSystemEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value("Preferences/Queueing/QueueingEnabled", false).toBool();
  }

  static int getMaxActiveDownloads() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Queueing/MaxActiveDownloads"), 3).toInt();
  }

  static int getMaxActiveUploads() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Queueing/MaxActiveUploads"), 3).toInt();
  }

  static int getMaxActiveTorrents() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value(QString::fromUtf8("Preferences/Queueing/MaxActiveTorrents"), 5).toInt();
  }

  static bool isWebUiEnabled() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value("Preferences/WebUI/Enabled", false).toBool();
  }

  static quint16 getWebUiPort() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value("Preferences/WebUI/Port", 8080).toInt();
  }

  static QString getWebUiUsername() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value("Preferences/WebUI/Username", "user").toString();
  }

  static QString getWebUiPassword() {
    QSettings settings("qBittorrent", "qBittorrent");
    return settings.value("Preferences/WebUI/Password", "").toString();
  }
};

#endif // PREFERENCES_H