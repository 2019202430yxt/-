#include "weapon.h"
#include "monster.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Weapon::ms_fixedSize(8, 8);

Weapon::Weapon(QPoint startPos, QPoint targetPoint, int harm, Monster *target,
               MainWindow *game, const QPixmap &sprite)
	: m_startPos(startPos)
	, m_targetPos(targetPoint)
	, m_sprite(sprite)
	, m_currentPos(startPos)
	, m_target(target)
	, m_game(game)
    , m_harm(harm)
{
}

void Weapon::draw(QPainter *painter) const
{
	painter->drawPixmap(m_currentPos, m_sprite);
}

void Weapon::move()
{
    // 80毫秒
    static const int duration = 80;
	QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
	animation->setDuration(duration);
	animation->setStartValue(m_startPos);
	animation->setEndValue(m_targetPos);
	connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
	animation->start();
}

void Weapon::hitTarget()
{
	if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(m_harm);
	m_game->removedBullet(this);
}

void Weapon::setCurrentPos(QPoint pos)
{
	m_currentPos = pos;
}

QPoint Weapon::currentPos() const
{
	return m_currentPos;
}
