/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006-2012  Christophe Dumez
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

#include "torrentcontentmodelfolder.h"

TorrentContentModelFolder::TorrentContentModelFolder(const QString& name, TorrentContentModelFolder* parent)
  : TorrentContentModelItem(parent)
{
  Q_ASSERT(parent);
  m_name = name;
  // Do not display incomplete extensions
  if (m_name.endsWith(".!qB"))
    m_name.chop(4);

  // Update parent
  m_parentItem->appendChild(this);
}

TorrentContentModelFolder::TorrentContentModelFolder(const QList<QVariant>& data)
  : TorrentContentModelItem(0)
{
  Q_ASSERT(data.size() == NB_COL);
  m_itemData = data;
}

TorrentContentModelFolder::~TorrentContentModelFolder()
{
  qDeleteAll(m_childItems);
}

void TorrentContentModelFolder::deleteAllChildren()
{
  Q_ASSERT(isRootItem());
  qDeleteAll(m_childItems);
  m_childItems.clear();
}

const QList<TorrentContentModelItem*>& TorrentContentModelFolder::children() const
{
  return m_childItems;
}

void TorrentContentModelFolder::appendChild(TorrentContentModelItem* item)
{
  Q_ASSERT(item);
  m_childItems.append(item);
}

TorrentContentModelItem* TorrentContentModelFolder::child(int row) const
{
  return m_childItems.value(row, 0);
}

TorrentContentModelFolder* TorrentContentModelFolder::childFolderWithName(const QString& name) const
{
  foreach (TorrentContentModelItem* child, m_childItems) {
    if (child->itemType() == FolderType && child->name() == name)
      return static_cast<TorrentContentModelFolder*>(child);
  }
  return 0;
}

int TorrentContentModelFolder::childCount() const
{
  return m_childItems.count();
}

// Only non-root folders use this function
void TorrentContentModelFolder::updatePriority()
{
  if (isRootItem())
    return;

  if (m_childItems.isEmpty())
    return;

  // If all children have the same priority
  // then the folder should have the same
  // priority
  const int prio = m_childItems.first()->priority();
  for (int i=1; i<m_childItems.size(); ++i) {
    if (m_childItems.at(i)->priority() != prio) {
      setPriority(prio::PARTIAL);
      return;
    }
  }
  // All child items have the same priority
  // Update own if necessary
  if (prio != priority())
    setPriority(prio);
}

void TorrentContentModelFolder::setPriority(int new_prio, bool update_parent)
{
  if (m_priority == new_prio)
    return;

  m_priority = new_prio;

  // Update parent priority
  if (update_parent)
    m_parentItem->updatePriority();

  // Update children
  if (m_priority != prio::PARTIAL) {
    foreach (TorrentContentModelItem* child, m_childItems)
      child->setPriority(m_priority, false);
  }

  updateSize();
  updateProgress();
}

void TorrentContentModelFolder::updateProgress()
{
  if (isRootItem())
    return;

  qulonglong total_done = 0;
  foreach (TorrentContentModelItem* child, m_childItems) {
    if (child->priority() > 0)
      total_done += child->totalDone();
  }

  Q_ASSERT(total_done <= m_size);
  if (total_done != m_totalDone) {
    m_totalDone = total_done;
    m_parentItem->updateProgress();
  }
}

void TorrentContentModelFolder::updateSize()
{
  if (isRootItem())
    return;

  qulonglong size = 0;
  foreach (TorrentContentModelItem* child, m_childItems) {
    if (child->priority() != prio::IGNORED)
      size += child->size();
  }

  if (size != m_size) {
    m_size = size;
    m_parentItem->updateSize();
  }
}
