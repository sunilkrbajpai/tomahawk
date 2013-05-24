/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2012, Michael Zanetti <mzanetti@kde.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DYNAMIC_QML_WIDGET_H
#define DYNAMIC_QML_WIDGET_H

#include "ViewPage.h"
#include "Typedefs.h"
#include "widgets/DeclarativeView.h"

#include <QDeclarativeImageProvider>

class PlayableModel;
class PlayableProxyModel;

namespace Tomahawk
{

class DynamicModel;

class DynamicQmlWidget : public DeclarativeView, public Tomahawk::ViewPage
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool configured READ configured NOTIFY configuredChanged)

public:
    explicit DynamicQmlWidget( const dynplaylist_ptr& playlist, QWidget* parent = 0 );
    virtual ~DynamicQmlWidget();

    virtual QWidget* widget() { return this; }
    virtual Tomahawk::playlistinterface_ptr playlistInterface() const;

    virtual QString title() const;
    virtual void setTitle(const QString &title);
    virtual QString description() const;
    virtual QString iconSource() const;

    virtual bool showInfoBar() const { return false; }
    virtual bool showModes() const { return false; }
    virtual bool showFilter() const { return false; }

    virtual bool jumpToCurrentTrack();

    playlist_ptr playlist() const;

    bool loading();
    bool configured();

signals:
    void loadingChanged();
    void configuredChanged();
    void titleChanged();

public slots:
    void playItem(int index);
    void pause();
    void startStationFromArtist(const QString &artist);
    void startStationFromGenre(const QString &genre);
    void startStationFromYear(int year);
    void startStationFromTo(int yearFrom, int yearTo);

private slots:
    void currentIndexChanged();
    void tracksGenerated( const QList< Tomahawk::query_ptr>& queries );
    void nextTrackGenerated( const Tomahawk::query_ptr& track );
    void error( const QString& title, const QString& body);

    void onRevisionLoaded( Tomahawk::DynamicPlaylistRevision );
    void playlistChanged( Tomahawk::playlistinterface_ptr pl );

    void resolvingFinished( bool hasResults );

    void trackStarted();
    void startStation();
    void stopStation( bool stopPlaying );

    void loadArtistCharts();
    void onArtistCharts( const QList< Tomahawk::artist_ptr >& artists );

private:
    DynamicModel* m_model;
    PlayableProxyModel* m_proxyModel;
    dynplaylist_ptr m_playlist;

    PlayableModel* m_artistChartsModel;

    bool m_runningOnDemand;
    bool m_activePlaylist;
    bool m_playNextResolved;
};

}

#endif // DYNAMIC_QML_WIDGET_H