BUILD_DIR = .build
GET_COMMIT = "git log -q |grep '^commit '|head -n1|cut -d' ' -f2"

default: all

.PHONY: all

all: clib build test

.PHONY: .FORCE
.FORCE:

clib:
	@clib install

build: 
	@test -d $(BUILD_DIR) && {  meson $(BUILD_DIR) --reconfigure; } || { meson $(BUILD_DIR); }

test:
	@meson test -C $(BUILD_DIR) --verbose

clean:
	@test -d $(BUILD_DIR) && rm -rf $(BUILD_DIR)

install:
	@echo Install OK

tidy:
	@./tidy.sh

pull: git-pull clib build test

clib-update:
	@./update_commit.sh

git-pull:
	@git pull

push: tidy
	@git commit -am 'automated git commit'
	@git push
