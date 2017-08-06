#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	gui.setup("gui", "settings.xml");
	gui.add(resolutionMesh.setup("Resolution Mesh", 4, 1, 20));
	gui.add(saveMesh.setup("save mesh", false));
	gui.add(extrusion.setup("extrusion", 0.5, 0, 400.0f));

	map.loadImage("image.jpg");
	width=map.getWidth();
	height=map.getHeight();

	fbo.allocate(width, height, GL_RGB);
	pix.allocate(width, height, OF_IMAGE_COLOR);


	

	pointLight.setDiffuseColor(ofColor(255.f, 255.f, 255.f));

	// specular color, the highlight/shininess color //
	pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
	pointLight.setDiffuseColor(ofColor(255,255,255));

	// shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess(64);
	material.setSpecularColor(ofColor(255, 255, 255));
	



}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(10, 10, 10), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);





	ofSetColor(255, 255, 255, 255);



	pointLight.setDiffuseColor(ofColor(255,255,255));
	material.setSpecularColor(ofColor(255,255,255));
	ofVboMesh mesh = drawMesh();
	ofEnableDepthTest();

	ofEnableLighting();
	cam.begin();

	pointLight.enable();
	pointLight.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0));
	//material.begin();



	mesh.drawFaces();
	//   mesh.smoothNormals(30);
	//mesh.drawWireframe();

	//material.end();
	pointLight.disable();
	cam.end();

	ofDisableLighting();
	ofDisableDepthTest();

	gui.draw();

	if (saveMesh) {
		mesh.save("mesh" + ofGetTimestampString() + ".ply");
		saveMesh = false;
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//pointLight.setPosition(x, y, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofVboMesh ofApp::drawMesh() {

	//cam.begin();
	ofPixels pixels;
	//ofFbo newFbo = FBO;
	ofImage img;
	//fbo.readToPixels(pixels);
	pixels = map;
	//img.setFromPixels(pixels);	
	int inc = resolutionMesh;
	pixels.resize(width / inc, height / inc);

	ofVboMesh mesh;
	int indexMesh = 0;

	for (int y = 0; y < pixels.getHeight(); y++) {
		for (int x = 0; x<pixels.getWidth(); x++) {


			//for (int i = 0; i < pixels.getHeight()*pixels.getWidth(); i++) {




			ofFloatColor sampleColor(
				pixels.getPixels()[(indexMesh * 3)] / 255.f,				// r
				pixels.getPixels()[(indexMesh * 3) + 1] / 255.f,			// g
				pixels.getPixels()[(indexMesh * 3) + 2] / 255.f);
			//ofColor sampleColor = pixels.getColor(indexMesh);
			//x + (y*pixels.getWidth());
			//cout << "index mesh" << indexMesh << " x"<<x<<" y"<<y<<endl;
			//pixels.getPixelIndex(x, y);
			//	cout << "index" << indexMesh << endl;

			mesh.addVertex(ofPoint(x, y, sampleColor.getBrightness() * extrusion));	// mesh index = x + y*width
																								// this replicates the pixel array within the camera bitmap...
			mesh.addColor(sampleColor);  // placeholder for colour data, we'll get this from the camera
			mesh.addNormal(ofPoint(x, y, (sampleColor.getBrightness() * extrusion) - 10));

			indexMesh++;

			//	indexMesh++;
		}
	}
	/*
	indexMesh = 0;
	for (int x = 0; x < pixels.getWidth(); x++) {
	for (int y = 0; y < pixels.getHeight(); y++) {

	mesh.addIndex(indexMesh);
	mesh.addIndex(indexMesh + pixels.getWidth());
	mesh.addIndex(indexMesh + 1 + pixels.getWidth());
	//
	mesh.addIndex(indexMesh);
	mesh.addIndex(indexMesh + 1);
	mesh.addIndex(indexMesh + 1 + pixels.getWidth());
	indexMesh ++;//pixels.getPixelIndex(x, y);

	}
	}
	*/
	//	}
	//	int newResW = FBO.getWidth() /inc;
	//	int newResH = FBO.getHeight() / inc;

	indexMesh = 0;
	for (int y = 0; y < pixels.getHeight() - 1; y += 1) { //
		for (int x = 0; x< pixels.getWidth() - 1; x += 1) {//

														   //for (int i = 0; i< pixels.getWidth()*pixels.getHeight(); i++) {

			mesh.addIndex(x + y*pixels.getWidth());				// 0
			mesh.addIndex((x + 1) + y*pixels.getWidth());			// 1
			mesh.addIndex(x + (y + 1)*pixels.getWidth());			// 10

			mesh.addIndex((x + 1) + y*pixels.getWidth());			// 1
			mesh.addIndex((x + 1) + (y + 1)*pixels.getWidth());		// 11
			mesh.addIndex(x + (y + 1)*pixels.getWidth());		// 10

																//	indexMesh = i;

																//	mesh.addIndex(i);
																//	mesh.addIndex(i+ pixels.getWidth());
																//	mesh.addIndex(i+ 1 + pixels.getWidth());
																//
																//	mesh.addIndex(i);
																//	mesh.addIndex(i + 1);
																//	mesh.addIndex(i + 1 + pixels.getWidth());

																//++;

		}
	}

	/*

	for (int i = 0; i<FBO.getWidth()*FBO.getHeight(); i++) {

	ofFloatColor sampleColor(pixels.getPixels()[i * 3] / 255.f,				// r
	pixels.getPixels()[i * 3 + 1] / 255.f,			// g
	pixels.getPixels()[i * 3 + 2] / 255.f);			// b
	//cout<<sampleColor<<endl;
	//now we get the vertex aat this position
	//we extrude the mesh based on it's brightness
	ofVec3f tmpVec =mesh.getVertex(i);
	tmpVec.z = sampleColor.getBrightness() * extrusion.getValue();
	mesh.setVertex(i, tmpVec);

	mesh.setColor(i, sampleColor);
	}
	*/




	return mesh;
}