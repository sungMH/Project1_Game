#include <bangtal>

using namespace  bangtal;

int main() {

	
	//씬1. 게임 시작화면
	auto startScene = Scene::create("임진왜란","images/게임시작화면.png");
	auto gameStartButton = Object::create("images/게임시작버튼.png", startScene,500,350);
	startScene->setOnEnterCallback([&](ScenePtr)->bool {
		showMessage("임진왜란 - 조선 1592년");
		return true;
		});

	//씬 1-2. 게임 설명
	auto manual = Scene::create("게임설명", "images/게임설명.png");
	auto nextB = Object::create("images/다음.png", manual,1000, 10);
	nextB->setScale(0.6f);

	

	//씬2. 게임 선택 화면- 한반도 사진과 주요 전장 선택
	auto map = Scene::create("조선 1592년 (임진년)", "images/지역선택화면.png");
	auto PyungYangGameButton = Object::create("images/평양성.png", map, 200, 400);
	auto TanGeumDaeGameButton = Object::create("images/탄금대.png", map, 500, 200);
	auto HaeJeonGameButton = Object::create("images/해전.png", map, 300, 50);
	auto quiz = Object::create("images/퀴즈.png", map, 1000, 300);

	PyungYangGameButton->setScale(0.3f);
	TanGeumDaeGameButton->setScale(0.3f);
	HaeJeonGameButton->setScale(0.7f);
	quiz->setScale(0.3f);

	gameStartButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
		});

	nextB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
		});
	map->setOnEnterCallback([&](ScenePtr)->bool {
		showMessage("참전하실 전장을 선택해 주세요");
		return true;
		});


	//씬3. 각 전장

	//3-1 퀴즈설명

	auto manualQuiz = Scene::create("퀴즈설명","images/퀴즈설명.png");
	auto nextB1 = Object::create("images/다음.png", manualQuiz, 1000, 10);
	auto prevB = Object::create("images/이전.png", manualQuiz, 10, 10);
	nextB1->setScale(0.6f);

	prevB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
		});
	quiz->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		manualQuiz->enter();
		return true;
		});

	//3-2 퀴즈고르기
	auto selectQuiz = Scene::create("임진왜란", "images/게임시작화면.png");
	auto iconPyung = Object::create("images/평양성전투.png", selectQuiz, 490, 315);
	auto iconTan = Object::create("images/탄금대전투.png", selectQuiz, 90, 315);
	auto iconHae = Object::create("images/해상전투.png", selectQuiz, 890 ,315);

	nextB1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		selectQuiz->enter();
		return true;
		});


	bool gethid1 = false, gethid2 = false, gethid3 = false; //히든아이템 획득여부
	auto quizPyung = Scene::create("평양성퀴즈", "images/평양성퀴즈.png");
	auto quizTan = Scene::create("탄금대퀴즈", "images/탄금대퀴즈.png");
	auto quizHae = Scene::create("해전퀴즈", "images/해전퀴즈.png");

	iconPyung->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (gethid1) {
			showMessage("이미 학습하셨습니다.");
		}
		else {
			quizPyung->enter();
		}
		return true;
		});
	iconTan->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (gethid2) {
			showMessage("이미 학습하셨습니다.");
		}
		else {
			quizTan->enter();
		}
		return true;
		});
	iconHae->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (gethid3) {
			showMessage("이미 학습하셨습니다.");
		}
		else {
			quizHae->enter();
		}
		return true;
		});

	//3-3 평양성 탄금대 해전 퀴즈
	auto box1 = Object::create("images/보물상자.png",quizPyung, 1000,10);
	auto box2 = Object::create("images/보물상자.png", quizTan, 1000, 10);
	auto box3 = Object::create("images/보물상자.png", quizHae, 1000, 10);
	box1->setScale(0.5f); box2->setScale(0.5f); box3->setScale(0.5f);
	bool box1_locked = true, box2_locked = true, box3_locked = true;
	auto keypad1 = Object::create("images/키패드.png", quizPyung, 1050, 60);
	auto keypad2 = Object::create("images/키패드.png", quizTan, 1050, 60);
	auto keypad3 = Object::create("images/키패드.png", quizHae, 1050, 60);
	keypad1->setScale(2.0f); keypad2->setScale(2.0f); keypad3->setScale(2.0f);
	auto hiddenItem1 = Object::create("images/불랑기포.png",quizPyung,0,0,false);
	auto hiddenItem2 = Object::create("images/신기전.png",quizTan,0,0,false);
	auto hiddenItem3 = Object::create("images/거북선.png", quizHae, 0, 0, false);
	auto previousIcon1 = Object::create("images/이전.png", quizPyung, 10, 10);
	auto previousIcon2= Object::create("images/이전.png", quizTan, 10, 10);
	auto previousIcon3 = Object::create("images/이전.png", quizHae, 10, 10);
	auto goMapButton1 = Object::create("images/gomap.png", quizPyung, 590, 10, false);
	auto goMapButton2 = Object::create("images/gomap.png", quizTan, 590, 10, false);
	auto goMapButton3 = Object::create("images/gomap.png", quizHae, 590, 10, false);

	keypad1->setOnMouseCallback([&](ObjectPtr , int , int , MouseAction )->bool {
		showKeypad("112", box1);//키패드암호, 키패드암호를 성공했을 때 이벤트를 수신할 곳
		return true;
		});
	box1->setOnKeypadCallback([&](ObjectPtr object)->bool {
		showMessage("불랑기포 획득: 평양성 전투에서 사용가능");
		box1_locked = false;
		return true;
		});
	box1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (box1_locked) {
			showMessage("금고를 열려면 비밀 번호가 필요하겠어.");
		}
		else {//열린상태
			hiddenItem1->pick();
			gethid1 = true;
			goMapButton1->show();
		}
		return true;
		});

	keypad2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		showKeypad("363", box2);//키패드암호, 키패드암호를 성공했을 때 이벤트를 수신할 곳
		return true;
		});
	box2->setOnKeypadCallback([&](ObjectPtr object)->bool {
		showMessage("신기전 획득: 탄금대 전투에서 사용가능");
		box2_locked = false;
		return true;
		});
	box2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (box2_locked) {
			showMessage("금고를 열려면 비밀 번호가 필요하겠어.");
		}
		else {//열린상태
			hiddenItem2->pick();
			gethid2 = true;
			goMapButton2->show();
		}
		return true;
		});

	keypad3->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		showKeypad("233", box3);//키패드암호, 키패드암호를 성공했을 때 이벤트를 수신할 곳
		return true;
		});
	box3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		showMessage("거북선 획득 :  해전에서 사용가능");
		box3_locked = false;
		return true;
		});
	box3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (box3_locked) {
			showMessage("금고를 열려면 비밀 번호가 필요하겠어.");
		}
		else {//열린상태
			hiddenItem3->pick();
			gethid3 = true;
			goMapButton3->show();
		}
		return true;
		});
	
	previousIcon1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		manualQuiz->enter();
		return true;
		});
	previousIcon2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		manualQuiz->enter();
		return true;
		});

	previousIcon3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		manualQuiz->enter();
		return true;
		});

	goMapButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		map->enter();
		return true;
		});
	goMapButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		map->enter();
		return true;
		});
	goMapButton3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		map->enter();
		return true;
		});

	//4.평양성 게임 생성

	//4-1게임 설명
	auto pManual1 = Scene::create("게임설명1","images/평양성게임설명1.png");
	auto pManual2 = Scene::create("게임설명2", "images/평양성게임설명2.png");
	auto pGameScene = Scene::create("평양성 수성전","images/성벽.png");
	auto nextP1 = Object::create("images/다음.png", pManual1, 1100, 10);
	auto nextP2 = Object::create("images/다음.png", pManual2, 1100, 10);
	nextP1->setScale(0.3f);
	nextP2->setScale(0.3f);
	auto prevP1 = Object::create("images/이전.png", pManual1, 60, 10);
	auto prevP2 = Object::create("images/이전.png", pManual2, 60, 10);
	auto timerP1 = Timer::create(1.5f);
	auto timerP2 = Timer::create(3.0f);
	auto timerP3 = Timer::create(4.5f);
	auto timerP4 = Timer::create(1.0f);

	PyungYangGameButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		pManual1->enter();
		return true;
		});
	nextP1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		pManual2->enter();
		return true;
		});
	nextP2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		pGameScene->enter();
		timerP1->start();
		timerP2->start();
		timerP3->start();
		timerP4->start();
		return true;
		});
	prevP1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
		});
	prevP2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		pManual1->enter();
		return true;
		});

	//4-2게임 구현

	auto soldierB = Object::create("images/병사준비버튼.png", pGameScene, 700, 650);
	auto officerB = Object::create("images/부장준비버튼.png", pGameScene, 900, 650);
	auto generalB = Object::create("images/장수준비버튼.png", pGameScene, 1100, 650);
	bool readySoldier = false, readyOfficer = false, readyGeneral = false;
	ObjectPtr soliders[11], officers[6], generals[3], enermies[31]; //병사 10, 부장 5, 장수 2, 왜군 30 큐로 저장
	int solFront = 0, offFront = 0, gerFront = 0, solRear = 0, offRear = 0, gerRear = 0, enerFront =0, enerRear = 0;
	int numSol = 0, numOff = 0, numGer = 0, numEner =0;

	timerP1->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(1.5f);
		soldierB->setImage("images/병사생성버튼.png");
		readySoldier = true;
		return true;
	});
	timerP2->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(1.5f);
		officerB->setImage("images/부장생성버튼.png");
		readyOfficer = true;
		return true;
	});
	timerP3->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(1.5f);
		generalB->setImage("images/장수생성버튼.png");
		readyGeneral = true;
		return true;
	});
	timerP4->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(1.0f);
		numEner++;
		if (numEner < 30) {
			enerRear = (enerRear + 1) % 30;
			enermies[enerRear] = Object::create("images/왜군.png", pGameScene,1200, 10);
			enermies[enerRear]->setOnMouseCallback([&](ObjectPtr, int x, int y, MouseAction)->bool {
				if (x <= 0) {
					endGame();//왜군이 우리 성 함락, 좀더 패배 조건 잘쓰기 메인화면으로 돌아가기나...등등
				}
				return true;
				});
			
		}
		return true;
		});

	soldierB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readySoldier == true) {
			soldierB->setImage("images/병사생성버튼.png");
			numSol++;//일정 이상 생성 불가 - 이건 병사 소멸 콜백때 다시 타이머 스타트 시켜야 할듯
			readySoldier = false;
			timerP1->start();
		}
		return true;
	});
	officerB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readyOfficer == true) {
			officerB->setImage("images/부장생성버튼.png");
			numOff++;
			readyOfficer = false;
			timerP2->start();
		}
		return true;
		});
	generalB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readyGeneral == true) {
			generalB->setImage("images/장수생성버튼.png");
			numGer++;
			readyGeneral = false;
			timerP3->start();
		}
		return true;
	});






















	//5.탄금대 게임 생성

	//5-1게임 설명
	auto tManual1 = Scene::create("게임설명1", "images/탄금대게임설명1.png");
	auto tManual2 = Scene::create("게임설명2", "images/탄금대게임설명2.png");
	auto tGameScene = Scene::create("탄금대 전투", "images/들판.png");
	auto nextT1 = Object::create("images/다음.png", tManual1, 1100, 10);
	auto nextT2 = Object::create("images/다음.png", tManual2, 1100, 10);
	nextT1->setScale(0.3f);
	nextT2->setScale(0.3f);
	auto prevT1 = Object::create("images/이전.png", tManual1, 60, 10);
	auto prevT2 = Object::create("images/이전.png", tManual2, 60, 10);

	TanGeumDaeGameButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		tManual1->enter();
		return true;
		});
	nextT1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		tManual2->enter();
		return true;
		});
	nextT2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		tGameScene->enter();
		return true;
		});
	prevT1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
		});
	prevT2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		tManual1->enter();
		return true;
		});

	//5-2게임 구현


	//6.해전 게임 생성

	//6-1게임 설명
	auto hManual1 = Scene::create("게임설명1", "images/해상게임설명1.png");
	auto hManual2 = Scene::create("게임설명2", "images/해상게임설명2.png");
	auto hGameScene = Scene::create("해상 전투", "images/바다.png");
	auto nextH1 = Object::create("images/다음.png", hManual1, 1100, 10);
	auto nextH2 = Object::create("images/다음.png", hManual2, 1100, 10);
	nextH1->setScale(0.3f);
	nextH2->setScale(0.3f);
	auto prevH1 = Object::create("images/이전.png", hManual1, 60, 10);
	auto prevH2 = Object::create("images/이전.png", hManual2, 60, 10);

	auto timer1 = Timer::create(1.5f);
	auto timer2 = Timer::create(1.5f);


	HaeJeonGameButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hManual1->enter();
		return true;
		});
	nextH1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hManual2->enter();
		timer1->start();
		timer2->start();
		return true;
		});
	nextH2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hGameScene->enter();
		return true;
		});
	prevH1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
		});
	prevH2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hManual1->enter();
		return true;
		});

	//6-2게임 구현
	/*
	auto button = Object::create("images/다음.png", hGameScene, 100, 100,false);
	auto button2 = Object::create("images/이전.png", hGameScene, 400, 100,false);


	timer1->setOnTimerCallback([&](TimerPtr timer)->bool {

		button->show();

		return true;
		});
	timer2->setOnTimerCallback([&](TimerPtr timer)->bool {

		button2->show();

		return true;
		});
		*/

	startGame(startScene);
}