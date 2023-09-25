#!/usr/bin/env python3
import autograde
import os, os.path

assignment_name = 'PA1'
release='1'

autograde.Test.time_limit = 60

class ArgFileTests(autograde.FileTests):
    Test = autograde.FileRefTest

    def get_tests(self, project, prog, build_dir, data_dir):
        test_group = project + ':' + self.name if self.name else project
        prog = './' + prog

        # gather names of reference files
        ref_names = [fname for fname in os.listdir(data_dir)
                        if fname.startswith(self.ref_prefix)
                        and fname.endswith(self.suffix)]
        ref_names.sort()

        # for each reference name, read the corresponding argument file
        for ref_name in ref_names:
            arg_name = self.arg_prefix + ref_name[len(self.ref_prefix):]

            arg_file = os.path.join(data_dir, arg_name)

            if not os.path.exists(arg_file):
                autograde.logger.warning('Unmatched reference file: %r', ref_name)
                continue

            args = [prog]
            with open(arg_file) as f:
                for line in f:
                    args.append(line.rstrip())

            ref = os.path.join(data_dir, ref_name)

            yield self.Test(
                cmd      = args,
                ref_file = ref,
                category = self.category,
                group    = test_group,
                weight   = self.weight,
                dir      = build_dir)

class ErrorTests(autograde.AbstractTestGroup):
    def __init__(self, **kws):
        super().__init__(**kws)
        self.file = 'tests' + self.id + '.txt'

    def get_tests(self, project, prog, build_dir, data_dir):
        test_group = project + ':' + self.id

        test_file = os.path.join(data_dir, self.file)

        if not os.path.exists(test_file):
            autograde.logger.warning('Test file not found: %r', test_file)
            return

        autograde.logger.debug('Opening tests file: %r', test_file)

        prog = './' + prog

        with open(test_file) as lines:
            for line in lines:
                yield autograde.Test(cmd      = [prog, line.rstrip()],
                                     ref_code = 1,
                                     category = self.category,
                                     group    = test_group,
                                     weight   = self.weight,
                                     dir      = build_dir)


assignment = autograde.MultiProject(
    autograde.StringTests.Project('rot13', weight=0.5),
    ArgFileTests.Project('sorta', weight=5/8),
    autograde.StdinFileTests.Project('list', weight=2),
    autograde.FileTests.Project('mexp', weight=2),
    autograde.Project('bst',
        autograde.StdinFileTests(id='1', weight=1.5),
        autograde.StdinFileTests(id='2', weight=1.5),
    ),
    autograde.Project('rpn',
        autograde.StringTests(id='1', weight=1.5),
        ErrorTests(id='2', weight=5/8),
    ),
)


if __name__ == '__main__':
    os.environ['LC_ALL'] = 'en-US'
    autograde.main(assignment_name, assignment, release)
