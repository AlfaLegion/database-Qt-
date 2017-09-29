#ifndef LABA_1_H
#define LABA_1_H

#include <QtWidgets/QMainWindow>
#include<QtSql>
#include<QtWidgets>

struct User
{
	QString host_name;
	QString user_name;
	QString DB_name;
	QString pass;
};
static bool createConnection(QSqlDatabase &database,const User& ur)
{
	database.setConnectOptions();
	database = QSqlDatabase::addDatabase("QMYSQL");
	database.setHostName(ur.host_name);
	database.setUserName(ur.user_name);
	database.setDatabaseName(ur.DB_name);
	database.setPassword(ur.pass);
	if (database.open())
	{
		//qDebug() << "OKkk";
		return true;
	}
	else 
	{
		//qDebug() << "mazafak";
		return false;
	}
}
class change_database :public QWidget
{
	Q_OBJECT
private:
	QComboBox* cmb;
	QLabel* lb_fl_1;
	QLineEdit* edit_fl_1;
	QLabel* lb_fl_2;
	QLineEdit* edit_fl_2;
	QLabel* lb_fl_3;
	QLineEdit* edit_fl_3;
	QPushButton* btn;

	QTextEdit* console;
	QSqlDatabase* db;
	QSqlQueryModel* model;
public:
	change_database(QTextEdit* buff,QSqlDatabase *temp,QSqlQueryModel* qur,QWidget* wgt = nullptr) :console(buff),db(temp),model(qur), QWidget(wgt)
	{
		setFixedSize(550, 200);
		setWindowTitle("Insert");
		cmb = new QComboBox(this);
		QStringList ls;
		ls <<"--"<<"table_1" << "table_2";
		cmb->addItems(ls);
		cmb->setEnabled(true);
		cmb->move(250, 20);
		
		lb_fl_1 = new QLabel(this);
		edit_fl_1 = new QLineEdit(this);
		lb_fl_1->setMinimumWidth(100);
		lb_fl_1->move(10, 50);
		edit_fl_1->move(10, 70);
		edit_fl_1->setMaximumWidth(150);

		lb_fl_2 = new QLabel(this);
		edit_fl_2 = new QLineEdit(this);
		lb_fl_2->setMinimumWidth(100);
		lb_fl_2->move(180, 50);
		edit_fl_2->move(180, 70);
		edit_fl_2->setMaximumWidth(150);

		lb_fl_3 = new QLabel(this);
		edit_fl_3 = new QLineEdit(this);
		lb_fl_3->setMinimumWidth(100);
		lb_fl_3->move(380, 50);
		edit_fl_3->move(380, 70);
		edit_fl_3->setMaximumWidth(150);

		btn = new QPushButton(this);
		btn->setText("Insert");
		btn->move(250, 120);

		QObject::connect(btn, SIGNAL(clicked()), this, SLOT(slotBtn()));
		QObject::connect(cmb, SIGNAL(activated(const QString&)), this, SLOT(slotCmb(const QString&)));
		setAttribute(Qt::WA_DeleteOnClose);
	}
public slots:
	void slotBtn()
	{
		if (cmb->currentText() != "--")
		{
			model->setQuery("INSERT INTO " + cmb->currentText() + " VALUES ( '" + edit_fl_1->text() + "','" + edit_fl_2->text() + "','" + edit_fl_3->text() + "');");
			if (db->lastError().isValid() || model->lastError().isValid())
			{
				if (db->lastError().isValid())
					console->append(db->lastError().text() + ".\n");
				else console->append(model->lastError().text() + ".\n");
			}
			else
				console->append("Successfully inserted.\n");
		}
		console = nullptr;
		db = nullptr;
		model = nullptr;
		this->close();
	}
	void slotCmb(const QString& str)
	{
		if (cmb->currentText() == "table_1")
		{
			lb_fl_1->setText("Name");
			lb_fl_2->setText("Mail");
			lb_fl_3->setText("ID");
		}
		else
		{
			lb_fl_1->setText("Country");
			lb_fl_2->setText("City");
			lb_fl_3->setText("ID");
		}
	}
};
class update_db :public QWidget
{
	Q_OBJECT
private:
	QTableView* view;
	QSqlTableModel* model;

	QPushButton* btn1;
	QPushButton *btn2;
	QComboBox* cmb;

	QTextEdit* console;
	QSqlDatabase* db;
public:
	update_db(QTextEdit* buff, QSqlDatabase *temp, QWidget* wgt = nullptr) :console(buff), db(temp), QWidget(wgt)
	{
		cmb = new QComboBox(this);
		QStringList ls;
		ls << "--" << "table_1" << "table_2";
		cmb->addItems(ls);
		cmb->move(10, 550);

		view = new QTableView(this);
		view->resize(650, 500);
		view->move(0, 0);

		model = new QSqlTableModel(this);
		model->setEditStrategy(QSqlTableModel::OnManualSubmit);

		
		btn1 = new QPushButton(this);
		btn2 = new QPushButton(this);
		btn1->setMinimumWidth(50);
		btn1->setText("Update");
		btn2->setMinimumWidth(50);
		btn2->setText("Cancel");
		btn1->move(10, 520);
		btn2->move(90, 520);

		QObject::connect(btn1, SIGNAL(clicked()), this, SLOT(slotBtn1()));
		QObject::connect(btn2, SIGNAL(clicked()), this, SLOT(slotBtn2()));
		QObject::connect(cmb, SIGNAL(activated(const QString&)), this, SLOT(slotCmb(const QString&)));

		setAttribute(Qt::WA_DeleteOnClose);
		setWindowTitle("Update");
		setFixedSize(650, 650);
	}
	public slots:
	void slotBtn1()
	{
		if (model->submitAll())
		{
			console->append("Successfully updated.\n");
		}
		else
		{
			model->revertAll();
			console->append(model->lastError().text() + ".\n");
		}
		console = nullptr;
		db = nullptr;
		close();
	}
	void slotBtn2()
	{
		model->revertAll();
		console = nullptr;
		db = nullptr;
		close();
	}
	void slotCmb(const QString& str)
	{
		if (cmb->currentText() == "table_1")
		{
			model->setTable(cmb->currentText());
			model->select();
			view->setModel(model);
		}
		if (cmb->currentText() == "table_2")
		{
			model->setTable(cmb->currentText());
			model->select();
			view->setModel(model);
		}
	}
};
class connection_wg :public QWidget
{
	Q_OBJECT
private:
	User *us;
	QLabel* lb2;
	QLineEdit* name_db;
	QLabel* lb3;
	QLineEdit* user;
	QLabel* lb4;
	QLineEdit* namehost;
	QLabel* lb5;
	QLineEdit* password;
	QPushButton* btn_connect;
	QSqlDatabase* db;
	QTextEdit* console;
public:
	connection_wg(QTextEdit* buff,QSqlDatabase* d,QWidget* wgt = nullptr) :console(buff),db(d),QWidget(wgt)
	{
		btn_connect = new QPushButton(this);
		btn_connect->setText("Connect");
		btn_connect->setMinimumSize(50, 20);
		btn_connect->setMaximumSize(51, 21);
		//name database
		lb2 = new QLabel(this);
		lb2->setText("Name of database");
		name_db = new QLineEdit(this);
		// name user
		lb3 = new QLabel(this);
		lb3->setText("User name");
		user = new QLineEdit;
		//name host
		lb4 = new QLabel(this);
		lb4->setText("Name host");
		namehost = new QLineEdit(this);
		//password
		lb5 = new QLabel(this);
		lb5->setText("Password");
		password = new QLineEdit(this);
		password->setEchoMode(QLineEdit::Password);
		//layout
		QHBoxLayout* hlay_2 = new QHBoxLayout;
		hlay_2->addWidget(name_db);
		hlay_2->addWidget(lb2);
		QHBoxLayout* hlay_3 = new QHBoxLayout;
		hlay_3->addWidget(user);
		hlay_3->addWidget(lb3);
		QHBoxLayout* hlay_4 = new QHBoxLayout;
		hlay_4->addWidget(namehost);
		hlay_4->addWidget(lb4);
		QHBoxLayout* hlay_5 = new QHBoxLayout;
		hlay_5->addWidget(password);
		hlay_5->addWidget(lb5);
		QHBoxLayout* hlaybtn = new QHBoxLayout;
		hlaybtn->addWidget(btn_connect);
		QVBoxLayout* vlay = new QVBoxLayout;
		vlay->addLayout(hlay_2);
		vlay->addLayout(hlay_3);
		vlay->addLayout(hlay_4);
		vlay->addLayout(hlay_5);
		vlay->addLayout(hlaybtn);
		setLayout(vlay);
		QObject::connect(btn_connect, SIGNAL(clicked()), this, SLOT(slotConnect()));
		setFixedSize(220, 220);
		setAttribute(Qt::WA_DeleteOnClose);
	}
public slots:
	void slotConnect()
	{
		us = new User;
		us->pass = password->text();
		us->host_name = namehost->text();
		us->DB_name = name_db->text();
		us->user_name = user->text();
		if (createConnection(*db, *us))
			console->append("Connected.\n");
		else console->append(db->lastError().text()+".\n");
		db = nullptr;
		console = nullptr;
		delete us;
		close();
	}
};
class delete_db :public QWidget
{
	Q_OBJECT
private:
	QLabel* lb_fl_3;
	QLineEdit* edit_fl_3;
	QPushButton* btn;

	QTextEdit* console;
	QSqlDatabase* db;
	QSqlQueryModel* model;
public:
	delete_db(QTextEdit* buff, QSqlDatabase *temp, QSqlQueryModel* qur, QWidget* wgt = nullptr) :console(buff), db(temp), model(qur), QWidget(wgt)
	{
		this->setAttribute(Qt::WA_DeleteOnClose);
		setFixedSize(300, 150);
		setWindowTitle("Delete");

		lb_fl_3=new QLabel(this);
		lb_fl_3->setText("Full name: ");
		lb_fl_3->setMinimumWidth(100);
		lb_fl_3->move(50,50);
		edit_fl_3=new QLineEdit(this);
		edit_fl_3->setMinimumWidth(150);
		edit_fl_3->move(130, 50);
		btn = new QPushButton(this);
		btn->setText("Delete");
		btn->setMinimumWidth(60);
		btn->move(120, 100);
		QObject::connect(btn, SIGNAL(clicked()), this, SLOT(slotBtn()));
	}
public slots:
	void slotBtn()
	{
		model->setQuery("DELETE FROM table_1 where name='" + edit_fl_3->text() + "';");
		if (db->lastError().isValid() || model->lastError().isValid())
		{
			if (db->lastError().isValid())
				console->append(db->lastError().text() + ".\n");
			else console->append(model->lastError().text() + ".\n");
		}
		else
			console->append("Successfully deleted.\n");
		console = nullptr;
		db = nullptr;
		model = nullptr;
		this->close();
	}
};
class MyWidget :public QWidget
{
	Q_OBJECT
private:
	
	QMenu* connect_m;
	QMenu* change_m;
	QMenu* select_m;
	QMenu* discon_m;
	QPushButton* connection;
	QPushButton* change_DB;
	QPushButton* select;
	QPushButton* disconnect;
	QTableView *view;
	QSqlQueryModel *model;
	QLabel* txt_cons;
	QTextEdit* console;
	connection_wg* con;
	User *uuu;
	QSqlDatabase db;

	change_database* ins;
	delete_db* del;
	update_db* upd;
public:
	MyWidget(QTextEdit* buff,QWidget *wgt = nullptr):QWidget(wgt),console(buff)
	{
		txt_cons = new QLabel(this);
		txt_cons->setText("Console:");
		txt_cons->move(10, 550);

		console = new QTextEdit(this);
		console->setReadOnly(true);
		console->move(20, 570);
		console->resize(650, 150);
		//button
		connection = new QPushButton("Connection");
		connection->setFlat(true);
		connection->setMinimumWidth(80);
		connection->setMaximumWidth(81);
		connection->setParent(this);
		connection->move(0, 10);

		change_DB = new QPushButton("Change DB");
		change_DB->setFlat(true);
		change_DB->setMinimumWidth(80);
		change_DB->setMaximumWidth(81);
		change_DB->setParent(this);
		change_DB->move(connection->width()+1, 10);

		select = new QPushButton("Select");
		select->setFlat(true);
		select->setParent(this);
		select->move(connection->width() + change_DB->width()+1, 10);
		select->setMinimumWidth(80);
		select->setMaximumWidth(81);

		disconnect= new QPushButton("Disconnect");
		disconnect->setFlat(true);
		disconnect->setParent(this);
		disconnect->move(connection->width() + change_DB->width() + select->width()+1, 10);
		disconnect->setMinimumWidth(80);
		disconnect->setMaximumWidth(81);
		//Menu
		connect_m = new QMenu(connection);
		connect_m->addAction("Connect",this,SLOT(slotConnect()));
		connection->setMenu(connect_m);

		change_m = new QMenu(change_DB);
		change_m->addAction("Insert",this,SLOT(slotInsert()));
		change_m->addAction("Update",this,SLOT(slotUpdate()));
		change_m->addAction("Delete",this,SLOT(slotDelete()));
		change_DB->setMenu(change_m);

		select_m = new QMenu(select);
		select_m->addAction("All inforamtion",this,SLOT(slotAllinf()));
		select_m->addAction("Show table 1", this, SLOT(slotShow_1()));
		select_m->addAction("Show table 2", this, SLOT(slotShow_2()));
		select->setMenu(select_m);

		discon_m = new QMenu(disconnect);
		discon_m->addAction("Current database", this, SLOT(slotDisconnect()));
		disconnect->setMenu(discon_m);
		// View
		view = new QTableView(this);
		view->resize(650, 500);
		view->move(20, 40);
		model = new QSqlQueryModel(this);
		setWindowTitle("DB MySQL");
		setFixedSize(700, 750);
	}
public slots:
	void slotAllinf()
	{
		QFile file;
		file.setFileName("All_info.txt");
		file.open(QIODevice::WriteOnly);
		QTextStream stm(&file);

		model->setQuery("SELECT NAME, MAIL, CITY,COUNTRY from TABLE_1,TABLE_2 WHERE TABLE_1.ID=TABLE_2.ID;");
		if (db.lastError().isValid()||model->lastError().isValid())
		{	
			if(db.lastError().isValid())
				console->append(db.lastError().text() + ".\n");
			else console->append(model->lastError().text() + ".\n");
		}
		else
		console->append("Query satisfied.\n");
		view->setModel(model);
		QSqlRecord rec = model->record();
		QSqlQuery rt = model->query();
		QString str1;
		QString str2;
		QString str3;
		QString str4;
		QString str5;
		while (model->query().next())
		{
			str1 = rt.value(rec.indexOf("name")).toString();
			str2 = rt.value(rec.indexOf("mail")).toString();
			str3 = rt.value(rec.indexOf("city")).toString();
			str4 = rt.value(rec.indexOf("country")).toString();
			str5 = rt.value(rec.indexOf("ID")).toString();
			stm<< "'"+str1 + "'  '" + str2 + "'  '" + str3+ "'  '" + str4+ "'  '" + str5+"'" << endl << endl;
		}
		file.close();
		stm.flush();
	}
	void slotShow_1()
	{
		QFile file;
		file.setFileName("table_1.txt");
		file.open(QIODevice::WriteOnly);
		QTextStream stm(&file);

		model->setQuery("SELECT* FROM TABLE_1;");
		if (db.lastError().isValid() || model->lastError().isValid())
		{
			if (db.lastError().isValid())
				console->append(db.lastError().text() + ".\n");
			else console->append(model->lastError().text() + ".\n");
		}
		else
			console->append("Query satisfied.\n");
		view->setModel(model);
		QSqlRecord rec = model->record();
		QSqlQuery rt = model->query();
		QString str1;
		QString str2;
		QString str3;
		while (model->query().next())
		{
			str1 = rt.value(rec.indexOf("name")).toString();
			str2 = rt.value(rec.indexOf("mail")).toString();
			str3 = rt.value(rec.indexOf("ID")).toString();
		stm << "'" + str1 + "'  '" + str2 + "'  '" + str3 + "'" << endl << endl;
		}
		file.close();
		stm.flush();
	}
	void slotShow_2()
	{
		QFile file;
		file.setFileName("table_2.txt");
		file.open(QIODevice::WriteOnly);
		QTextStream stm(&file);

		model->setQuery("SELECT* FROM TABLE_2;");
		if (db.lastError().isValid() || model->lastError().isValid())
		{
			if (db.lastError().isValid())
				console->append(db.lastError().text() + ".\n");
			else console->append(model->lastError().text() + ".\n");
		}
		else
			console->append("Query satisfied.\n");
		view->setModel(model);
		QSqlRecord rec = model->record();
		QSqlQuery rt = model->query();
		QString str1;
		QString str2;
		QString str3;
		while (model->query().next())
		{
			str1 = rt.value(rec.indexOf("city")).toString();
			str2 = rt.value(rec.indexOf("country")).toString();
			str3 = rt.value(rec.indexOf("ID")).toString();
			stm << "'" + str1 + "'  '" + str2 + "'  '" + str3 + "'" << endl << endl;
		}
		file.close();
		stm.flush();
	}
	void slotConnect()
	{
		con = new connection_wg(console,&db);
		con->show();
	}
	void slotDisconnect()
	{/*model->clear();
		console->clear();*/
		if (db.isValid())
		{
			db.close();
			db.removeDatabase(db.connectionName());
			console->setPlainText("Disconnect");
		}
		else
		{
			console->append("No connection.\n");
		}
	}
	void slotDelete()
	{
		del = new delete_db(console, &db, model);
		del->show();
	}
	void slotInsert()
	{
		ins = new change_database(console, &db, model);
		ins->show();
	}
	void slotUpdate()
	{
		upd = new update_db(console, &db);
		upd->show();
	}
};


#endif // LABA_1_H
