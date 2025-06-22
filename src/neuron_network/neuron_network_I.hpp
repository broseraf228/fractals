#pragma once

struct uVecF;

class NeuronNetworkI {
protected:
	NeuronNetworkI() = default;
public:
	virtual const uVecF& getOutput() const = 0;
	virtual void setInput(const uVecF&) = 0;
	virtual void forward() = 0;
};