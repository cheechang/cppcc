#pragma once
#define CONNECT_CTRL(CTRL_PTR1,CTRL_PTR2,SGINAL,EVENT) QObject::connect(CTRL_PTR1.get(), SIGNAL(SGINAL), CTRL_PTR2.get(), SLOT(on##EVENT), Qt::QueuedConnection);
#define CONNECT_SUBCTRL(SUB_CTRL_PTR, EVENT) QObject::connect(SUB_CTRL_PTR.get(), SIGNAL(EVENT), this, SLOT(on##EVENT), Qt::QueuedConnection);
#define CONNECT_SERVICE(EVENT) QObject::connect(this, SIGNAL(signalSer##EVENT), this, SLOT(onSer##EVENT), Qt::QueuedConnection);
#define DISCONNECT_SERVICE(EVENT) QObject::disconnect(this, SIGNAL(signalSer##EVENT), this, SLOT(onSer##EVENT));