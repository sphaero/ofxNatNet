#pragma once

#include "ofMain.h"

class ofxNatNet
{
	class InternalThread;
	friend class InternalThread;

public:

	typedef ofVec3f Marker;

	struct MarkerSet
	{
		string name;
		vector<Marker> markers;
	};

	struct RigidBody
	{
		int id;
		ofVec3f pos;
		ofQuaternion orientation;
		vector<Marker> markers;
		float mean_marker_error;

		ofMatrix4x4 getMatrix() const
		{
			ofMatrix4x4 matrix;
			matrix.setTranslation(pos);
			matrix.setRotate(orientation);
			return matrix;
		}

		bool found() const
		{
			return pos != ofVec3f(0, 0, 0);
		}
	};

	ofxNatNet() : thread(NULL) {}
	~ofxNatNet() { dispose(); }

	void setup(string network_interface_ip = "", string multicast_group = "239.255.42.99", int command_port = 1510, int data_port = 1511);
	void update();

	bool isConnected();
	int getFrameNumber() { return frame_number; }
	float getLatency() { return latency; }

	float getDataRate();

	void setScale(float v);
	float getScale();

	inline const size_t getNumMarker() { return markers.size(); }
	inline const Marker& getMarker(size_t index) { return markers[index]; }

	inline const size_t getNumMarkerSet() { return markersets.size(); }
	inline const MarkerSet& getMarkerSet(size_t index) { return markersets[index]; }

	inline const size_t getNumRigidBody() { return rigidbodies.size(); }
	inline const RigidBody& getRigidBody(size_t index) { return rigidbodies[index]; }

	inline const vector<Marker>& getMarkers() { return markers; }
	inline const vector<MarkerSet>& getMarkerSet() { return markersets; }
	inline const vector<RigidBody>& getRigidBodies() { return rigidbodies; }

	void setBufferSize(int n);
	int getBufferSize();

protected:

	InternalThread *thread;

	int frame_number;
	float latency;

	vector<Marker> markers;
	vector<MarkerSet> markersets;
	vector<RigidBody> rigidbodies;

	void dispose();

private:

	ofxNatNet(const ofxNatNet&);
	ofxNatNet& operator=(const ofxNatNet&);

};
