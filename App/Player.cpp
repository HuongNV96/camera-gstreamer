#include "Player.h"
#include <QUrl>
#include <QDebug>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/ElementFactory>
#include <QGst/Bus>

Q_DECLARE_METATYPE(QGst::ElementPtr)

Player::Player(QObject *parent)
    : QObject(parent)
{
}

void Player::play()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePlaying);
    }
}

void Player::pause()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePaused);
    }
}

void Player::stop()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StateNull);
    }
}

void Player::setUri(const QString & uri)
{
    if (uri == mUri) {
        return;
    }
    if (!m_pipeline) {
        m_pipeline = QGst::ElementFactory::make("playbin").dynamicCast<QGst::Pipeline>();
        if (m_pipeline) {
            m_pipeline->setProperty("video-sink", m_surface->videoSink());

            //watch the bus for messages
            QGst::BusPtr bus = m_pipeline->bus();
            bus->addSignalWatch();
            QGlib::connect(bus, "message", this, &Player::onBusMessage);
        } else {
            qCritical() << "Failed to create the pipeline";
        }
    }

    if (m_pipeline) {
        m_pipeline->setProperty("uri", uri);
    }
    emit uriChanged();
}

void Player::onBusMessage(const QGst::MessagePtr & message)
{
    switch (message->type()) {
    case QGst::MessageEos: //End of stream. We reached the end of the file.
        stop();
        break;
    case QGst::MessageError: //Some error occurred.
        qCritical() << message.staticCast<QGst::ErrorMessage>()->error();
        stop();
        break;
    default:
        break;
    }
}
