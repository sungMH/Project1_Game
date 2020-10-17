#include <bangtal>
#include<iostream>
#include <ctime>
using namespace  bangtal;




int main() {

	
	//씬1. 게임 시작화면
	auto lastS = Scene::create("게임승리!", "images/최종화면.png");
	auto startScene = Scene::create("임진왜란","images/게임시작화면.png");
	auto victory = Scene::create("승리!", "images/만세.png");
	auto goMapB = Object::create("images/지도로돌아가기버튼.png", victory, 60, 500);
	auto endB = Object::create("images/게임종료버튼.png", victory, 960, 500);
	auto gameStartButton = Object::create("images/게임시작버튼.png", startScene,580,150);
	auto gameEndButton = Object::create("images/게임종료.png", startScene, 700, 150);
	auto endB2 = Object::create("images/게임종료버튼.png", lastS, 810, 20);
	auto goStart = Object::create("images/시작화면.png", lastS, 170, 20);

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
	bool clearP = false, clearT = false, clearH = false;

	PyungYangGameButton->setScale(0.3f);
	TanGeumDaeGameButton->setScale(0.3f);
	HaeJeonGameButton->setScale(0.7f);
	quiz->setScale(0.3f);


	gameEndButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		endGame();
		return true;
		});
	goMapB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		return true;
	});
	endB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		endGame();
		return true;
		});
	endB2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		endGame();
		return true;
		});


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

	goStart->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		gethid1 = false; gethid2 = false; gethid3 = false;
		clearT = false; clearP = false; clearH = false;
		hiddenItem1->drop(); hiddenItem2->drop(); hiddenItem3->drop();
		box1_locked = false, box2_locked = false, box3_locked = false;
		startScene->enter();
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
	auto timerPH = Timer::create(10.0f);
	auto timerP1 = Timer::create(2.0f);
	auto timerP2 = Timer::create(6.0f);
	auto timerP3 = Timer::create(8.0f);
	auto timerP4 = Timer::create(0.0f);
	auto timerP = Timer::create(20.f);

	PyungYangGameButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (clearP) {
			showMessage("평양성 전투 clear 하신 상태입니다! 다른 전장을 도와주십쇼!");
		}
		else {
			pManual1->enter();
		}
		return true;
		});
	nextP1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		pManual2->enter();
		return true;
		});
	nextP2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		pGameScene->enter();
		timerPH->start(); timerPH->set(10.0f);
		timerP1->start(); timerP1->set(2.0f);
		timerP2->start(); timerP2->set(6.0f);
		timerP3->start(); timerP3->set(8.0f);
		timerP4->start(); timerP4->set(2.0f);
		timerP->start(); timerP->set(60.0f);
		showTimer(timerP);
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

	
	auto endSceneP = Scene::create("평양성 함락", "images/평양성함락.png");
	auto endPB = Object::create("images/게임종료버튼.png", endSceneP, 900, 100);
	auto goMapPB = Object::create("images/지도로돌아가기버튼.png", endSceneP, 900, 400);
	auto hiddenP = Object::create("images/불랑기포.png", pGameScene, 10, 30,false);
	auto hiddenB = Object::create("images/불랑기포장전버튼.png", pGameScene, 200, 650, false);
	auto soldierB = Object::create("images/병사준비버튼.png", pGameScene, 400, 650);
	auto officerB = Object::create("images/부장준비버튼.png", pGameScene, 600, 650);
	auto generalB = Object::create("images/장수준비버튼.png", pGameScene, 800, 650);
	bool readySoldier = false, readyOfficer = false, readyGeneral = false, ener = false, pushOther = false,readyHidden = false;
	hiddenP->setScale(0.2f);




	//평양성 전투
   //구조체로 선언
	ObjectPtr soldiers[11], officers[6], generals[3], enermies[31]; //병사 10, 부장 5, 장수 2, 왜군 30 큐로 저장
	int solFront = 0, offFront = 0, gerFront = 0, solRear = 0, offRear = 0, gerRear = 0, enerFront = 0, enerRear = 0;
	int numSol = 0, numOff = 0, numGer = 0, numEner = 0;
	int lifeOff[6] = { 0, }, lifeGer[3] = { 0, };//부장은 왜군 2명과 싸우면 전사, 장수는 왜군 3명과 싸우면 전사
	int locateSol[11] = { 0, }, locateOff[6] = { 0, }, locateGer[3] = { 0, }, locateEner[31] ;
	double sT = 10.0f, oT = 25.0f, gT = 30.0f, hT = 10.0f,eT =1.0f,gameTimeP = 90.0f;

	endPB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		endGame();
		return true;
		});

	goMapPB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		timerPH->set(hT);
		timerP1->set(sT);
		timerP2->set(oT);
		timerP3->set(gT);
		timerP4->set(eT);
		timerP->set(gameTimeP);
		hiddenB->setImage("images/불랑기포장전버튼.png");
		readyHidden = false;
		while (enerFront != enerRear) {
			enerFront++;
			enermies[enerFront]->hide();
		}
		numEner = 0;
		if (clearT && clearH && clearP) {
			lastS->enter();
		}
		return true;
	});

	hiddenB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readyHidden == true && pushOther == false) {
			while (enerFront != enerRear) {
				enerFront++;
				enermies[enerFront]->hide();
			}
			numEner = 0;
			readyHidden = false;
			hiddenB->setImage("images/불랑기포장전버튼.png");
			timerPH->set(hT);
			timerPH->start();
		}
		return true;
		});



	timerP->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(gameTimeP);
		timer->stop();
		timerPH->stop();
		timerP1->stop();
		timerP2->stop();
		timerP3->stop();
		timerP4->stop();
		showMessage("평양성전투 클리어!");
		hideTimer();
		victory->enter();
		return true;
		});
	timerPH->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(hT);
		hiddenB->setImage("images/불랑기포발사버튼.png");
		readyHidden = true;
		return true;
		});

	timerP1->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(sT);
		soldierB->setImage("images/병사생성버튼.png");
		readySoldier = true;
		return true;
	});
	timerP2->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(oT);
		officerB->setImage("images/부장생성버튼.png");
		readyOfficer = true;
		return true;
	});
	timerP3->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(gT);
		generalB->setImage("images/장수생성버튼.png");
		readyGeneral = true;
		return true;
	});
	timerP4->setOnTimerCallback([&](TimerPtr timer)->bool {
		timer->set(eT);
		pushOther = false;
		
		//병사 부장 장수 왜군 이동, 한 번에 80이동
		int sF = solFront , sR = solRear, oF = offFront  , oR = offRear, gF = gerFront,gR = gerRear,eF = enerFront, eR = enerRear;
		
		//병사이동
		while (sF != sR) {
			sF = (sF + 1) % 11;
			locateSol[sF] = locateSol[sF] + 80;
			soldiers[sF]->locate(pGameScene, locateSol[sF], 10);
		}
		//부장이동
		while (oF != oR) {
			oF = (oF + 1) % 6;
			locateOff[oF] = locateOff[oF] + 80;
			officers[oF]->locate(pGameScene, locateOff[oF], 10);
		}
		//장수이동
		while (gF != gR) {
			gF = (gF + 1) % 3;
			locateGer[gF] = locateGer[gF] + 80;
			generals[gF]->locate(pGameScene, locateGer[gF], 10);
		}
		//왜군이동
		while (eF != eR) {
			eF = (eF + 1) % 31;
			locateEner[eF] = locateEner[eF] - 80;
			enermies[eF]->locate(pGameScene, locateEner[eF], 10);
			if (locateEner[eF] <= 0) {
				endSceneP->enter();
				hideTimer();
				showMessage("적들이 평양성을 넘었습니다! GAME OVER!");
				timerPH->stop();
				timerP1->stop();
				timerP2->stop();
				timerP3->stop();
				timerP4->stop();
				timerP->stop();
				break;
			}
		}
		
		//왜군과 병사가 전투한다면
		int f =solFront, r = solRear, es =(enerFront + 1)%31;
	
		while (f != r && enerFront != enerRear) {
			//왜군과 우리 병사가 겹친다면
			f = (f + 1) % 11;
			if (locateSol[f] >= locateEner[es]) {
				enerFront = (enerFront + 1) % 31;
				soldiers[f]->hide();
				enermies[es]->hide();
				solFront = (solFront + 1) % 11;
				numSol--;
				numEner--;
				locateSol[f] = 0;
				locateEner[es] = 1280;
				break;
			}
		}

		//왜군과 장수가 전투한다면
		f = gerFront , r = gerRear, es =( enerFront + 1)%31;
		while (f != r && enerFront != enerRear) {
			f = (f + 1) % 3;
			if (locateGer[f] >= locateEner[es]) {
				enerFront = (enerFront + 1) % 31;
				enermies[es]->hide();
				numEner--;
				locateEner[es] = 1280;
				if (lifeGer[f] == 1) {//목숨 1개라면
					locateGer[f] = 0;
					numGer--;
					gerFront = (gerFront + 1) % 3;
					generals[f]->hide();
				}
				else {//목숨이 2개,3개라면
					lifeGer[f] = lifeGer[f] - 1;
				}
				break;
			}
		}

		//왜군과 부장이 전투한다면
		f = offFront , r = offRear, es = (enerFront + 1)%31;
		while (f != r && enerFront != enerRear) {
			f = (f + 1) % 6;
			if (locateOff[f] >= locateEner[es]) {
				enerFront = (enerFront + 1) % 31;
				enermies[es]->hide();
				numEner--;
				locateEner[es] = 1280;
				if (lifeOff[f] == 1) {//목숨 1개라면
					locateOff[f] = 0;
					numOff--;
					offFront = (offFront + 1) % 6;
					officers[f]->hide();
				}
				else {//목숨이 2개라면
					lifeOff[f] = lifeOff[f] - 1;
				}
				break;
			}
		}

		if (numEner < 30) {
			numEner++;
			enerRear = (enerRear + 1) % 31;
			locateEner[enerRear] = 1280;
			if (ener == false) {
				enermies[enerRear] = Object::create("images/왜군.png", pGameScene, 1280, 10);
				ener = true;
			}
			else {
				enermies[enerRear] = Object::create("images/왜군2.png", pGameScene, 1280, 10);
				ener = false;
			}
		}
		timerP4->start();


		if (gethid1){//불랑기포를 얻었다면
			hiddenP->show();
			hiddenB->show();
			timerPH->start();
		}
		return true;
	});

	soldierB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readySoldier == true && pushOther == false) {
			soldierB->setImage("images/병사준비버튼.png");
			if (numSol < 10) {
				numSol++;//일정 이상 생성 불가 - 이건 병사 소멸 콜백때 다시 타이머 스타트 시켜야 할듯
				solRear = (solRear + 1) % 11;
				soldiers[solRear] = Object::create("images/병사.png", pGameScene, 0, 10);
				locateSol[solRear] = 0;
				readySoldier = false;
				pushOther = true;
				timerP1->start();

			}
		}
		return true;
	});
	officerB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readyOfficer == true && pushOther == false) {
			officerB->setImage("images/부장준비버튼.png");
			if (numOff < 5) {
				numOff++;
				offRear = (offRear + 1) % 6;
				officers[offRear] = Object::create("images/부장.png", pGameScene, 0, 10);
				lifeOff[offRear] = 2;
				locateOff[offRear] = 0;
				readyOfficer = false;
				pushOther = true;
				timerP2->start();
			}
		}
		return true;
	});
	generalB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (readyGeneral == true && pushOther == false) {
			generalB->setImage("images/장수준비버튼.png");
			if (numGer < 2) {
				numGer++;
				gerRear = (gerRear + 1) % 3;
				generals[gerRear] = Object::create("images/장수.png", pGameScene, 0, 10);
				lifeGer[gerRear] = 3;
				locateGer[gerRear] = 0;
				readyGeneral = false;
				pushOther = true;
				timerP3->start();
			}
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
	srand((unsigned int)time(NULL));
	int point[6][8] = {0,};

	TanGeumDaeGameButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (clearT) {
			showMessage("탄금대 전투 clear 하신 상태입니다! 다른 전장을 도와주십쇼!");
		}
		else {
			tManual1->enter();
		}
		return true;
		});
	nextT1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		tManual2->enter();
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
	double gameTime = 6.0f;
	auto failScene = Scene::create("패배", "images/탄금대패배.png");
	auto myCharacter = Object::create("images/기병.png", tGameScene,0,120);
	auto startBT = Object::create("images/탄금대시작버튼.png", tGameScene, 415, 200);
	auto timerT = Timer::create(gameTime);
	auto upB = Object::create("images/위쪽.png", tGameScene, 300,650);
	auto downB = Object::create("images/아래쪽.png", tGameScene, 430, 650);
	auto leftB = Object::create("images/왼쪽.png", tGameScene, 560, 650);
	auto rightB = Object::create("images/오른쪽.png", tGameScene, 690, 650);
	auto hiddenT = Object::create("images/신기전.png", tGameScene, 0, 470, false);
	auto hiddenTB = Object::create("images/신기전발포버튼.png", tGameScene,820, 650, false);
	auto endTB = Object::create("images/게임종료버튼.png", failScene, 900, 100);
	auto goMapTB = Object::create("images/지도로돌아가기버튼.png", failScene, 900, 400);
	ObjectPtr gunner[4];
	ObjectPtr brrier[20];
	int numOfBarrier = 0;
	int whereBarrier[20][2];
	int myX = 0, myY = 120;


	nextT2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		tGameScene->enter();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				int k = rand() % 5;
				point[k][i * 2] = 1;
			}
		}
		myCharacter->locate(tGameScene, 0, 170);
		startBT->show();
		
		return true;
		});

	for (int i = 0; i < 4; i++) {
		gunner[i] = Object::create("images/조총병.png", tGameScene, 1200, 20 + i * 150);
	}

	endTB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		endGame();
		return true;
		});

	goMapTB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		for (int i = 0; i < numOfBarrier; i++) {;
			brrier[i]->hide();
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				point[i][j] = 0;
			}
		}
		hiddenT->setImage("images/신기전.png");
		hiddenTB->show();
		myX = 0, myY = 120;
		numOfBarrier = 0;
		timerT->set(gameTime);
		timerT->stop();
		if (clearT && clearH && clearP) {
			lastS->enter();
		}
		return true;
		});

	upB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (myY <= 520) {
			myY += 100;
			myCharacter->locate(tGameScene, myX, myY);
			for (int i = 0; i < 20; i++) {
				if (whereBarrier[i][0] == myX && whereBarrier[i][1] == myY) {
					timerT->set(gameTime);
					timerT->stop();
					failScene->enter();
					hideTimer();
				}
			}
		}
		return true;
	});
	downB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (myY >= 20) {
			myY -= 100;
			myCharacter->locate(tGameScene, myX, myY);
			for (int i = 0; i < 20; i++) {
				if (whereBarrier[i][0] == myX && whereBarrier[i][1] == myY) {
					timerT->set(gameTime);
					timerT->stop();
					failScene->enter();
					hideTimer();
				}
			}
		}
		return true;
	});
	leftB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (myX >= 100) {
			myX -= 100;
			myCharacter->locate(tGameScene, myX, myY);
			for (int i = 0; i < 20; i++) {
				if (whereBarrier[i][0] == myX && whereBarrier[i][1] == myY) {
					timerT->set(gameTime);
					timerT->stop();
					failScene->enter();
					hideTimer();
				}
			}
		}
		return true;
	});
	rightB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		myX += 100;
		myCharacter->locate(tGameScene, myX, myY);
		for (int i = 0; i < 20; i++) {
			if (whereBarrier[i][0] == myX && whereBarrier[i][1] == myY) {
				timerT->set(gameTime);
				timerT->stop();
				failScene->enter();
				hideTimer();
			}
		}
		if (myX >= 1280) {
			timerT->set(gameTime);
			timerT->stop();
			hideTimer();
			victory->enter();
			clearT = true;
		}
		return true;
	});

	timerT->setOnTimerCallback([&](TimerPtr timer)->bool {
		timerT->set(gameTime);
		timerT->stop();
		hideTimer();
		failScene->enter();
		return true;
		});

	hiddenTB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hiddenT->setImage("images/신기전발사.png");
		hiddenTB->hide();
		timerT->set(gameTime);
		timerT->start();
		return true;
		});

	startBT->setOnMouseCallback([&](ObjectPtr o, int, int, MouseAction)->bool {
		o->hide();
		showTimer(timerT);
		timerT->start();
		if (gethid2) {
			hiddenT->show();
			hiddenTB->show();
		}

		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 8; j++){
				if (point[i][j] == 1) {
					brrier[numOfBarrier] = Object::create("images/목책.png", tGameScene, 400 + 100 * j, 20 + i * 100);
					whereBarrier[numOfBarrier][0] = 400 + 100 * j;
					whereBarrier[numOfBarrier][1] = 20 + i * 100;
					numOfBarrier++;
				}
			}
		}
		return true;
		});



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
	double setFireTime = 5.0f, moveFireTime = 2.0f, moveEnermyTime = 2.0f,lev1=30.0f,lev2 =20.0f,lev3 =10.0f;
	auto timerSFT = Timer::create(setFireTime);
	auto timerMFT = Timer::create(moveFireTime);
	auto timerMET = Timer::create(moveEnermyTime);
	auto timerLevel = Timer::create(lev1);
	auto failH = Scene::create("패배", "images/해전패배.png");
	auto endHB = Object::create("images/게임종료버튼.png", failScene, 900, 100);
	auto goMapHB = Object::create("images/지도로돌아가기버튼.png", failScene, 900, 400);
	auto hiddenShip1 = Object::create("images/거북선1.png", hGameScene, 600, 20, false);
	auto hiddenShip2 = Object::create("images/거북선1.png", hGameScene, 600, 420, false);

	HaeJeonGameButton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (clearH) {
			showMessage("해상 전투 clear 하신 상태입니다! 다른 전장을 도와주십쇼!");
		}
		else {
			hManual1->enter();
		}
		return true;
		});
	nextH1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hManual2->enter();
		return true;
		});
	nextH2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		hGameScene->enter();
		timerSFT->start();
		timerMFT->start();
		timerMET->start();
		timerLevel->set(lev1); timerLevel->stop();
		if (gethid3){
			hiddenShip1->show();
			hiddenShip2->show();
		}
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

	//6-2. 게임구현

	auto ship = Object::create("images/판옥선1.png", hGameScene, 0, 220);
	int shipX = 0, shipY = 220;
	ObjectPtr fire[51]; 
	ObjectPtr enerm[51];
	int pointFire[51][2]; int pointEner[51][2];
	int fireFront = 0, fireRear = 0, enFront =0, enRear = 0;
	auto upBH = Object::create("images/위쪽.png", hGameScene, 300, 650);
	auto downBH = Object::create("images/아래쪽.png", hGameScene, 430, 650);
	auto leftBH = Object::create("images/왼쪽.png", hGameScene, 560, 650);
	auto rightBH = Object::create("images/오른쪽.png", hGameScene, 690, 650);
	auto fireB = Object::create("images/함포장전.png", hGameScene, 820,650);
	bool readyFire = false;
	bool level1 = true, level2 = false, level3 = false;


	endTB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		endGame();
		return true;
		});

	goMapTB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		map->enter();
		shipX = 0, shipY = 220;
		level2 = false; level3 = false;
		moveEnermyTime = 2.0f;
		timerSFT->set(setFireTime); timerSFT->stop();
		timerMFT->set(moveFireTime); timerMFT->stop();
		timerMET->set(moveEnermyTime); timerMET->stop();
		timerLevel->set(lev1); timerLevel->stop();

		int i = fireFront, j = fireRear;
		while (i != j) {
			i = (i + 1) % 51;
			fire[i] ->hide();
		}
		i = enFront, j = enRear;
		while (i != j) {
			i = (i + 1) % 51;
			enerm[i]->hide();
		}
		ship->locate(hGameScene, 0, 220);
		enRear = 0; enFront = 0;
		fireFront = 0; fireRear = 0;
		if (clearT && clearH && clearP) {
			lastS->enter();
		}
		return true;
		});

	
	timerSFT->setOnTimerCallback([&](TimerPtr timer)->bool {
		fireB->setImage("images/함포사격.png");
		readyFire = true;
		return true;
		});

	timerMFT->setOnTimerCallback([&](TimerPtr timer)->bool {
		int i = fireFront, j = fireRear;
		while (i != j) {
			i = (i + 1) % 51;
			pointFire[i][0] += 80;
			fire[i]->locate(hGameScene, pointFire[i][0],pointFire[i][1]);
			int k = enFront, l = enRear;
			while (k != l) {
				k = (k + 1) % 51;
				if (pointEner[k][1] == pointFire[i][1] && pointEner[k][0] <= pointFire[i][0]) {
					fire[i]->hide();
					enerm[k]->hide();
					fireFront = (fireFront + 1) % 51;
					enerFront = (enerFront + 1) % 51;
					break;
				}
			}
		}
		
		timerMFT->set(moveFireTime);
		timerMFT->start();
		return true;
		});
	timerLevel->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (level2 == false) {
			level2 = true;
			moveEnermyTime = 1.0f;
			timerLevel->set(lev2);
			timerLevel->start();
			showMessage("적들의 진군속도가 빨라졌습니다!");
		}
		else if(level3 == false) {
			level3 = true;
			moveEnermyTime = 0.5f;
			timerLevel->set(lev3);
			timerLevel->start();
			showMessage("적들의 진군속도가 빨라졌습니다!");
		}
		else {//승리
			victory->enter();
			clearH = true;
		}

		return true;
		});


	timerMET->setOnTimerCallback([&](TimerPtr timer)->bool {
		int a[3] = {0,0,0};
		for (int i = 0; i < 3; i++) {
			int j = rand() % 3;
			a[j] = 1;
		}
		
		int i = enFront, j = enRear;
		while (i != j) {
			i = (i + 1) % 51;
			pointEner[i][0] -= 80;
			if (pointEner[i][0] <= 0) {
				failH->enter();
			}

			if (gethid3 && pointEner[i][0] <= 900 && (pointEner[i][1] ==20 || pointEner[i][1] == 420)) {
				enerm[i]->hide();
				enerFront = (enerFront + 1) % 51;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (a[i] == 1) {
				enRear = (enRear + 1) % 51;
				enerm[enRear] = Object::create("images/안택선.png", hGameScene, 1280, 20 + i * 200);
				pointEner[enRear][0] = 1280;
				pointEner[enRear][1] = 20 + i * 200;
			}
		}
		timerMET->set(moveEnermyTime);
		timerMET->start();
		return true;
		});

	fireB->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (fireFront != fireRear) {
			readyFire = false;
			fireRear = (fireRear + 1) % 51;
			fire[fireRear] = Object::create("images/포탄", hGameScene, shipX + 300, shipY + 60);
			pointFire[fireRear][0] = shipX + 300;
			pointFire[fireRear][1] = shipY + 60;
			timerT->set(setFireTime);
			timerT->start();
		}
		return true;
		});

	upBH->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (shipY <= 420) {
			shipY += 200;
			ship->locate(hGameScene, shipX, shipY);
		}
		return true;
		});
	downBH->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (shipY >= 220) {
			shipY -= 200;
			ship->locate(hGameScene, shipX, shipY);
		}
			return true;
		});
	leftBH->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (shipX >= 300) {
			shipX -= 300;
			ship->locate(hGameScene, shipX, shipY);
		}
		return true;
		});
	rightBH->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (shipX <= 960){
			shipX += 300;
			ship->locate(hGameScene, shipX, shipY);
		}
		return true;
		});

	startGame(startScene);
}