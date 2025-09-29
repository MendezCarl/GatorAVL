

// uncomment and replace the following with your own headers

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "AVL.h"
#include <sstream>
using namespace std;
//
// // the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
// TEST_CASE("Example Test Name - Change me!", "[hello]"){
// 	// instantiate any class members that you need to test here
// 	int one = 1;
//
// 	// anything that evaluates to false in a REQUIRE block will result in a failing test
// 	REQUIRE(one == 0); // fix me!
//
// 	// all REQUIRE blocks must evaluate to true for the whole test to pass
// 	REQUIRE(true); // also fix me!
// }
// //
// TEST_CASE("Test 2", "[flag]"){
// 	// you can also use "sections" to share setup code between tests, for example:
// 	int one = 1;
//
// 	SECTION("num is 2") {
// 		int num = one + 1;
// 		REQUIRE(num == 2);
// 	};
//
// 	SECTION("num is 3") {
// 		int num = one + 2;
// 		REQUIRE(num == 3);
// 	};
//
// 	SECTION("num is 8") {
// 		int num = one + 10;
// 		REQUIRE(num == 8);
// 	}

	// each section runs the setup code independently to ensure that they don't affect each other
// }
//
// // you must write 5 unique, meaningful tests for credit on the testing portion of this project!
//
// // the provided test from the template is below.
//
// TEST_CASE("Example BST Insert", "[flag]"){
// 	/*
// 		MyAVLTree tree;   // Create a Tree object
// 		tree.insert(3);
// 		tree.insert(2);
// 		tree.insert(1);
// 		std::vector<int> actualOutput = tree.inorder();
// 		std::vector<int> expectedOutput = {1, 2, 3};
// 		REQUIRE(expectedOutput.size() == actualOutput.size());
// 		REQUIRE(actualOutput == expectedOutput);
// 	*/
// }

TEST_CASE("Inserting new users") {
	SECTION("Doesn't add identical users") {
		AVL tree;
		std::stringstream text;
		// std::streambuf* prev = std::cout.rdbuf(text.rdbuf());

		tree.insert("John Doe", 94298000);
		tree.insert("John Doe",94298000);

		// std::cout.rdbuf(prev);
		// std::string rawOutput = R"successful\nunsuccessful";
		// REQUIRE(rawOutput == text);

		std::vector<int> output = tree.inorder();
		REQUIRE(output.size() == 1);
	};

	SECTION("Doesn't add users who weren't given a 8 digit ID") {
		AVL tree;
		tree.insert("John Doe","xf231459");
		tree.insert("John Moon", 34765);
		tree.insert("john door");

		std::vector<int> output = tree.inorder();
		REQUIRE(output.empty());
	};

	SECTION("Does add user with correct parameters") {
		AVL tree;
		tree.insert("John Doe", 12345678);

		std::vector<int> output = tree.inorder();
		REQUIRE(output.size() == 1);
	};
}

TEST_CASE("Left Rotation") {
	SECTION("Tree is right-right") {
		AVL tree;
		tree.insert("John Doe",94298000);
		tree.insert("John Doee",94298001);
		tree.insert("John Doeeee",94298002);

		std::vector<int> output = tree.inorder();
		std::vector<int> expectedOutput = {94298000, 94298001, 94298002};
		std::vector<int> eachNodeBalanceFactor = tree.balanceFactor();
		for (int bf: eachNodeBalanceFactor) {
			REQUIRE(bf >= -1 );
			REQUIRE(bf <= 1);
		}

		REQUIRE(output.size() == expectedOutput.size());
		REQUIRE(output == expectedOutput);
	};

	SECTION("Tree is right-right with children") {
		AVL tree;
		tree.insert("John Doe",94298000);
		tree.insert("John Doee",94297897);
		tree.insert("John Doeee",94298003);
		tree.insert("John Doeeee",94298002);
		tree.insert("John Doeeeee",94298006);
		tree.insert("John Doeeeeee",94298106);
		tree.insert("John Doeeeeeee",94298005);

		std::vector<int> output = tree.inorder();
		std::vector<int> expectedOutput = {94297897, 94298000, 94298002, 94298003, 94298005, 94298006, 94298106};
		std::vector<int> eachNodeBalanceFactor = tree.balanceFactor();
		for (int bf: eachNodeBalanceFactor) {
			REQUIRE(bf >= -1 );
			REQUIRE(bf <= 1);
		}

		REQUIRE(output == expectedOutput);

	};
}

TEST_CASE("Right Rotation") {
	SECTION("Tree is left-left") {
		AVL tree;
		tree.insert("John Doe",94298000);
		tree.insert("John Doee",94297999);
		tree.insert("John Doeeee",94297998);

		std::vector<int> output = tree.inorder();
		std::vector<int> expectedOutput = {94297998, 94297999, 94298000};
		std::vector<int> eachNodeBalanceFactor = tree.balanceFactor();
		for (int bf: eachNodeBalanceFactor) {
			REQUIRE(bf >= -1 );
			REQUIRE(bf <= 1);
		}

		REQUIRE(output.size() == expectedOutput.size());
		REQUIRE(output == expectedOutput);
	}

	SECTION("Tree is left-right") {
		AVL tree;
		tree.insert("John Doe",94298000);
		tree.insert("John Doee",94297999);
		tree.insert("John Doeeee",94298001);

		std::vector<int> output = tree.inorder();
		std::vector<int> expectedOutput = {94297999, 94298000, 94298001};
		std::vector<int> eachNodeBalanceFactor = tree.balanceFactor();
		for (int bf: eachNodeBalanceFactor) {
			REQUIRE(bf >= -1 );
			REQUIRE(bf <= 1);
		}

		REQUIRE(output.size() == expectedOutput.size());
		REQUIRE(output == expectedOutput);
	}

	SECTION("Tree is left left with children") {
		AVL tree;
		tree.insert("John Doe",94298000);
		tree.insert("John Doee",94297999);
		tree.insert("John Doeee",94297998);
		tree.insert("John Doeeee",94297997);
		tree.insert("John Doeeeee",94297996);
		tree.insert("John Doeeeeee",94297995);
		tree.insert("John Doeeeeeee",94297994);

		std::vector<int> output = tree.inorder();
		std::vector<int> expectedOutput = {94297994, 94297995, 94297996, 94297997, 94297998, 94297999, 94298000};
		std::vector<int> eachNodeBalanceFactor = tree.balanceFactor();
		for (int bf: eachNodeBalanceFactor) {
			REQUIRE(bf >= -1 );
			REQUIRE(bf <= 1);
		}

		REQUIRE(output.size() == expectedOutput.size());
		REQUIRE(output == expectedOutput);
	}
}
//Carlos Mendez, 94298000