# Contributing to Casper C++ SDK

The following is a set of rules and guidelines for contributing to this repository. Please feel free to propose changes to this document in a pull request.

#### Table Of Contents

[Submitting issues](#submitting-issues)

[Guidelines](#guidelines)

[Contributing to Casper C++ SDK](#how-to-contribute)

## Submitting issues
If you have questions about how to use Casper C++ SDK, please direct these to the related discord channels:
* [#smart-contracts](https://discord.gg/casperblockchain)
* [#sdk-development](https://discord.gg/casperblockchain)

### Guidelines
* Please search the existing issues first, it's likely that your issue was already reported or even fixed.
  - Go to the main page of the repository, click "issues" and type any word in the top search/command bar.
  - You can also filter by appending e. g. "state:open" to the search string.
  - More info on [search syntax within GitHub](https://help.github.com/articles/searching-issues)

## How to contribute

All contributions to this repository are considered to be licensed under Apache License 2.0.

Workflow for bug fixes:
* Check open issues and unmerged pull requests to make sure the topic is not already covered elsewhere
* Fork the repository
* Do your changes on your fork
* Make sure to add or update relevant test cases
* Create a pull request, with a suitable title and description, referring to the related issue

Use your real name (sorry, no pseudonyms or anonymous contributions).
If you set your `user.name` and `user.email` git configs, you can sign your
commit automatically with `git commit -s`. You can also use git [aliases](https://git-scm.com/book/tr/v2/Git-Basics-Git-Aliases)
like `git config --global alias.ci 'commit -s'`. Now you can commit with
`git ci` and the commit will be signed.
