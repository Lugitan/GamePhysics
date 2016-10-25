#include "CppUnitTest.h"
#include "MassSpringSystemSimulator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimulatorTester
{		
	TEST_CLASS(PublicMassSpringSystemTests)
	{
	public: 
		TEST_METHOD(TestNumberofMassPoints)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->notifyCaseChanged(1);
			Assert::AreEqual(2.0f,(float)msss->getNumberOfMassPoints(),0.0001f,L"Number of Mass Points is not equal to 2",LINE_INFO());
		}
		TEST_METHOD(TestNumberofSprings)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();;
			msss->notifyCaseChanged(1);
			Assert::AreEqual(1.0f,(float)msss->getNumberOfSprings(),0.0001f,L"Number of Mass Points is not equal to 1",LINE_INFO());
		}
		TEST_METHOD(TestPositionOfMassPointsInitially)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->setMass(0.01f);
			msss->setStiffness(25.0f);
			msss->setDampingFactor(0.01f);
			msss->notifyCaseChanged(1);
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(0).x,0.0001f,L"Mass Point at index 0, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(0).y,0.0001f,L"Mass Point at index 0, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(0).z,0.0001f,L"Mass Point at index 0, Z value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(1).x,0.0001f,L"Mass Point at index 1, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(2.0f,(float)msss->getPositionOfMassPoint(1).y,0.0001f,L"Mass Point at index 1, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(1).z,0.0001f,L"Mass Point at index 1, Z value is wrong !!",LINE_INFO());
		}

		TEST_METHOD(TestPositionOfMassPointsAfter10TimeStepEuler)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->setMass(0.01f);
			msss->setStiffness(25.0f);
			msss->setDampingFactor(0.01f);
			DrawingUtilitiesClass * DUC = new DrawingUtilitiesClass();
			msss->initUI(DUC);
			msss->setIntegrator(EULER);
			msss->notifyCaseChanged(1);
			for(int i =0; i <10; i++)
				msss->simulateTimestep(0.005);;
			Assert::AreEqual(-0.04994f,(float)msss->getPositionOfMassPoint(0).x,0.0001f,L"Mass Point at index 0, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.00449f,(float)msss->getPositionOfMassPoint(0).y,0.0001f,L"Mass Point at index 0, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(0).z,0.0001f,L"Mass Point at index 0, Z value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.04994f,(float)msss->getPositionOfMassPoint(1).x,0.0001f,L"Mass Point at index 1, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(1.9955f,(float)msss->getPositionOfMassPoint(1).y,0.0001f,L"Mass Point at index 1, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(1).z,0.0001f,L"Mass Point at index 1, Z value is wrong !!",LINE_INFO());
		}

		TEST_METHOD(TestPositionOfMassPointsAfter10TimeStepMidPoint)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->setMass(0.01f);
			msss->setStiffness(25.0f);
			msss->setDampingFactor(0.01f);
			DrawingUtilitiesClass * DUC = new DrawingUtilitiesClass();
			msss->initUI(DUC);
			msss->setIntegrator(MIDPOINT);
			msss->notifyCaseChanged(1);
			for(int i =0; i <10; i++)
				msss->simulateTimestep(0.005);
			Assert::AreEqual(-0.0499164f,(float)msss->getPositionOfMassPoint(0).x,0.0001f,L"Mass Point at index 0, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0049928f,(float)msss->getPositionOfMassPoint(0).y,0.0001f,L"Mass Point at index 0, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(0).z,0.0001f,L"Mass Point at index 0, Z value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0499164f,(float)msss->getPositionOfMassPoint(1).x,0.0001f,L"Mass Point at index 1, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(1.99501f,(float)msss->getPositionOfMassPoint(1).y,0.0001f,L"Mass Point at index 1, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getPositionOfMassPoint(1).z,0.0001f,L"Mass Point at index 1, Z value is wrong !!",LINE_INFO());
		}

		TEST_METHOD(TestVelocityOfMassPointsInitially)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->setMass(0.01f);
			msss->setStiffness(25.0f);
			msss->setDampingFactor(0.01f);
			msss->notifyCaseChanged(1);
			Assert::AreEqual(-1.0f,(float)msss->getVelocityOfMassPoint(0).x,0.0001f,L"Mass Point at index 0, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(0).y,0.0001f,L"Mass Point at index 0, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(0).z,0.0001f,L"Mass Point at index 0, Z value is wrong !!",LINE_INFO());
			Assert::AreEqual(1.0f,(float)msss->getVelocityOfMassPoint(1).x,0.0001f,L"Mass Point at index 1, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(1).y,0.0001f,L"Mass Point at index 1, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(1).z,0.0001f,L"Mass Point at index 1, Z value is wrong !!",LINE_INFO());
		}

		TEST_METHOD(TestVelocityOfMassPointsAfter10TimeStepEuler)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->setMass(0.01f);
			msss->setStiffness(25.0f);
			msss->setDampingFactor(0.01f);
			DrawingUtilitiesClass * DUC = new DrawingUtilitiesClass();
			msss->initUI(DUC);
			msss->setIntegrator(EULER);
			msss->notifyCaseChanged(1);
			for(int i =0; i <10; i++)
				msss->simulateTimestep(0.005);
			Assert::AreEqual(-0.995508f,(float)msss->getVelocityOfMassPoint(0).x,0.0001f,L"Mass Point at index 0, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.199592f,(float)msss->getVelocityOfMassPoint(0).y,0.0001f,L"Mass Point at index 0, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(0).z,0.0001f,L"Mass Point at index 0, Z value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.995508f,(float)msss->getVelocityOfMassPoint(1).x,0.0001f,L"Mass Point at index 1, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(-0.199592f,(float)msss->getVelocityOfMassPoint(1).y,0.0001f,L"Mass Point at index 1, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(1).z,0.0001f,L"Mass Point at index 1, Z value is wrong !!",LINE_INFO());
		}

		TEST_METHOD(TestVelocityOfMassPointsAfter10TimeStepMidPoint)
		{
			MassSpringSystemSimulator * msss =  new MassSpringSystemSimulator();
			msss->setMass(0.01f);
			msss->setStiffness(25.0f);
			msss->setDampingFactor(0.01f);
			DrawingUtilitiesClass * DUC = new DrawingUtilitiesClass();
			msss->initUI(DUC);
			msss->setIntegrator(MIDPOINT);
			msss->notifyCaseChanged(1);
			for(int i =0; i <10; i++)
				msss->simulateTimestep(0.005);
			Assert::AreEqual(-0.995013f,(float)msss->getVelocityOfMassPoint(0).x,0.0001f,L"Mass Point at index 0, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.199424f,(float)msss->getVelocityOfMassPoint(0).y,0.0001f,L"Mass Point at index 0, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(0).z,0.0001f,L"Mass Point at index 0, Z value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.995013f,(float)msss->getVelocityOfMassPoint(1).x,0.0001f,L"Mass Point at index 1, X value is wrong !!",LINE_INFO());
			Assert::AreEqual(-0.199424f,(float)msss->getVelocityOfMassPoint(1).y,0.0001f,L"Mass Point at index 1, Y value is wrong !!",LINE_INFO());
			Assert::AreEqual(0.0f,(float)msss->getVelocityOfMassPoint(1).z,0.0001f,L"Mass Point at index 1, Z value is wrong !!",LINE_INFO());
		}

	};
}