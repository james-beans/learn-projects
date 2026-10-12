CXX ?= clang++
CXXFLAGS ?= -std=c++23

TARGETS = \
	dist/bp \
	dist/convertemp \
	dist/gtn \
	dist/hypotenuse \
	dist/qg \
	dist/rectangleloop \
	dist/reg \
	dist/rps \
	dist/tcalc \
	dist/ccv \
	dist/ttt

.PHONY: all clean directories

all: directories $(TARGETS)
	@echo ""
	@echo "Compiled all programs."
	@echo ""

directories:
	@mkdir -p dist

clean:
	@echo "Safely removing existing 'dist' directory contents..."
	@find dist -mindepth 1 -delete 2>/dev/null || true
	@rmdir dist 2>/dev/null || true

dist/bp: projects/bp.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/convertemp: projects/convertemp.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/gtn: projects/gtn.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/hypotenuse: projects/hypotenuse.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/qg: projects/qg.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/rectangleloop: projects/rectangleloop.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/reg: projects/reg.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/rps: projects/rps.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/tcalc: projects/tcalc.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/ccv: projects/ccv.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dist/ttt: projects/ttt.cpp
	$(CXX) $(CXXFLAGS) $< -o $@