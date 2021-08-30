#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_list.clear();
	this->frame_list.clear();
	this->edge_list.clear();

	auto noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01);

	for (int radius = 50; radius < 350; radius += 30) {

		ofMesh face, frame, edge;
		frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		for (int deg = 0; deg <= 360; deg += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto z = ofMap(ofNoise(glm::vec3(location * 0.005, ofGetFrameNum() * 0.05)), 0, 1, 0, radius) * ofMap(noise_value, 0, 1, 0, 2);
			auto line_z =  z / 10; // ³‚µ‚­‚ÍAz * 1.1;

			face.addVertex(glm::vec3(location, 0));
			face.addVertex(glm::vec3(location, z));

			frame.addVertex(glm::vec3(location, 0));
			frame.addVertex(glm::vec3(location, z));

			edge.addVertex(glm::vec3(location, z));
			edge.addVertex(glm::vec3(location, line_z));

			edge.addColor(ofColor(39));
			edge.addColor(ofColor(239));

			if (face.getNumVertices() > 2) {

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 4);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 3);
				frame.addIndex(frame.getNumVertices() - 2); frame.addIndex(frame.getNumVertices() - 4);

				edge.addIndex(face.getNumVertices() - 1); edge.addIndex(face.getNumVertices() - 2); edge.addIndex(face.getNumVertices() - 4);
				edge.addIndex(face.getNumVertices() - 1); edge.addIndex(face.getNumVertices() - 3); edge.addIndex(face.getNumVertices() - 4);
			}
		}

		this->face_list.push_back(face);
		this->frame_list.push_back(frame);
		this->edge_list.push_back(edge);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->face_list.size(); i++) {

		ofSetColor(39);
		this->face_list[i].drawFaces();

		ofSetColor(239);
		this->frame_list[i].drawWireframe();
		this->edge_list[i].drawFaces();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}