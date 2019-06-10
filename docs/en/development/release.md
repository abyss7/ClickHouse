# Release Cycle

This document describes the internal practices on how we do releases, how often and how we maintain them later.

## What is a Release?
Release is a bundle of binary packages from a specific unmodified commit in git-repository, that has been tested against all known automated tests.

There are 3 types of releases, which potentially differ in stability, and that's what we want from them:

- **testing**: automatically emerges from the master-branch with a given frequency, i.e. nightly builds.
- **prestable**: meets some minimal QA tests and shouldn't break any already working scenarios.
- **stable**: is tested in real-life conditions, got fixes for all known critical problems and has passed acceptance-tests of potential product users.

In reality it's not always possible to force everybody to test all of our releases, so for now we roll them on schedule and make sure that older ones get more bug-fixes over time.

Each type of release forms a channel. The user may subscribe to channel and get only a certain quality updates:

- **testing** is updated every day and is good to checkout some new features.
- **prestable** is updated every week.
- **stable** is also updated every week.

To track the stabilization progress of specific features within series of releases we use advanced versioning system.

## Versioning

The internal ClickHouse version is uniquely determined for every commit and requires the building from a git working-copy.

The overall version looks like `vYY.XX.ZZ.CC` and contains 4 numbers:

- **YY** is a major version and stands for the current year, e.g. `19`.
- **XX** is a minor version and is incremented for every new stable-branch, it starts from `1` every new year.
- **ZZ** is a release number that is unique for every release inside a specific stable-branch, it starts from `1`. For master-branch it's always `0`.
- **CC** is a number of commits since the last branch-point. It's very helpful to distinguish official and developer builds from the same branch.

### git-repository
