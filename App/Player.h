#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGst/Pipeline>
#include <QGst/Message>
#include <QGst/Quick/VideoSurface>
#include <QGst/Utils/ApplicationSink>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    ~Player() {
        if (m_pipeline) {
            m_pipeline->setState(QGst::StateNull);
            m_pipeline.clear();
        }
        delete m_surface;
    }

    Q_PROPERTY(QGst::Quick::VideoSurface *videoSurface READ videoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)

signals:
    void videoSurfaceChanged();
    void uriChanged();

public Q_SLOTS:
    void play();
    void pause();
    void stop();
    void setUri(const QString & uri);

    QGst::Quick::VideoSurface *videoSurface() const {
        return m_surface;
    }

    QString uri() const {
        return mUri;
    }

private:
    void onBusMessage(const QGst::MessagePtr & message);

    QGst::PipelinePtr m_pipeline;
    QGst::Quick::VideoSurface * m_surface = new QGst::Quick::VideoSurface();
    QString mUri;
};

#endif // PLAYER_H
